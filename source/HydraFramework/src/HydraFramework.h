#ifndef HYDRAPROCESS_H
#define HYDRAPROCESS_H

#include "pch.h"
#include "BSLib/Pattern/Singleton.h"
#include "BSLib/CriticalSectionScoped.h"
#include "utils/ThreadPool.h"
#include "BSLib/Utility/ClassLink.h"
#include "DataManager/RefDataManager.h"

///////////////////////////////////////////////////////////
// GlobalData

namespace GlobalData
{
    extern char         SecretKey[21];
    extern uint16_t     CustomMsgID[];
}

///////////////////////////////////////////////////////////
// HydraFramework
class CMsg;

namespace HydraFramework
{
    struct ClassEntry {
        void* pointer;
        const char* name;
    };

    struct SessionInfo {
        WORD wServerBodyID;
        ASTR szName;
    };

    enum DB {
        ACCOUNT,
        SHARD,
        LOG
    };

    typedef std::map<DB, std::string> db_map_t;
    typedef std::map<DWORD, SessionInfo> session_map_t;

    class CMainProcess: public CSingletonT<CMainProcess> {
        friend class CSingletonT<CMainProcess>;

    public:
        static bool CreateInstance(void* ptr, const char* name)
        {
            if (GetSingletonPtr()) return false;
            static CMainProcess init(ptr, name);
            return true;
        }

        const std::string GetVersion() { return m_version; }

        const std::string GetModuleName(void *ptr);

        void* GetModuleInstance(const char* moduleName);

        void HandleCustomMsg(CMsg *pMsg);
        void HandleMsg(CMsg *pMsg);

        CCriticalSection& GetCS() { return m_cs; }

        void SetConnectionString(const db_map_t& newMap);

        std::string GetConnectionString(DB dbType);

        DWORD GetSessionID(const std::string &module);

        void AddSessionID(DWORD dwSessionID, SessionInfo &sessInfo);

        void DelSessionID(DWORD dwSessionID);

        const stra_t& GetSettingFile() { return m_dllName; }

    private:
        CMainProcess(void* ptr, const char* className);
        virtual ~CMainProcess();

    private:
        CThreadPool* m_threadPool;
        CCriticalSection m_cs;
        const char* m_version;
        std::vector<ClassEntry> m_className;
        db_map_t m_db;
        session_map_t m_sessions;
        stra_t m_dllName;

        CMainProcess(const CMainProcess&);
        CMainProcess& operator=(const CMainProcess&);
    };
}

#define g_pHydraMainProcess (&HydraFramework::CMainProcess::GetSingleton())

#endif
