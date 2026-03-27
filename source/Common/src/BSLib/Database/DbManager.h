#pragma once

#include "DbConnectionPool.h"
#include "DbInstance.h"
#include "BSLib/CriticalSectionScoped.h"
#include "BSLib/Pattern/Singleton.h"
#include "stdext.h"

enum DbType {
    ACCOUNT,
    SHARD,
    LOG,
    MAX_DB
};

class CDbManager : public CSingletonT<CDbManager>
{
public:
    // Meyers' Singleton: Created once, persists for the app lifetime[cite: 1]
    static bool CreateInstance(BYTE min, BYTE max)
    {
        if (GetSingletonPtr()) return false;

        // Static local ensures automatic cleanup on exit
        static CDbManager instance;
        instance.m_dbMinConn = min;
        instance.m_dbMaxConn = max;

        return true;
    }

    int InitDB(const std::string& ini);

    // Original style accessors
    CDbInstance& GetInstance(DbType type);
    CDbConnection* GetConnection(DbType type);
    void Release(DbType type, CDbConnection *pDbConn);

    // Optimized shorthand for logic threads
    CDbInstance& GetAccountDB() { return m_dbInstancePool[ACCOUNT]; }
    CDbInstance& GetShardDB()   { return m_dbInstancePool[SHARD]; }
    CDbInstance& GetLogDB()     { return m_dbInstancePool[LOG]; }

private:
    CDbManager();
    virtual ~CDbManager();

    __inifile m_cfg; // Maps to stdext::inifile[cite: 2]
    BYTE m_dbMinConn;
    BYTE m_dbMaxConn;

    CDbConnectionPool m_dbPools[MAX_DB];
    CDbInstance       m_dbInstancePool[MAX_DB];
    CCriticalSection  m_cs;

    // Strict Singleton: No copies allowed
    CDbManager(const CDbManager&);
    CDbManager& operator=(const CDbManager&);
};

#define g_pDbMgr CDbManager::GetSingletonPtr()