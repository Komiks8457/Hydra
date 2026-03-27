#include "DbManager.h"

// Required for CSingletonT template
template <> CDbManager* CSingletonT<CDbManager>::s_pObject = NULL;

CDbManager::CDbManager() : m_dbMinConn(1), m_dbMaxConn(2)
{}

CDbManager::~CDbManager()
{
    // C++98 compliant loop
    for (int i = 0; i < MAX_DB; ++i) {
        m_dbPools[i].Shutdown();
    }
}

int CDbManager::InitDB(const std::string& ini)
{
    if (!m_cfg.load(ini))
        return -999;

    char szConnStr[512];
    const char* connStrFormat = "DRIVER={SQL Server};SERVER=%s;UID=%s;PWD=%s;DATABASE=%s;Trusted_Connection=true;";

    // Extraction using stdext::inifile::getvalue
    const std::string host    = m_cfg.getvalue("Database", "Host", "NULL");
    const std::string user    = m_cfg.getvalue("Database", "User", "NULL");
    const std::string pass    = m_cfg.getvalue("Database", "Pass", "NULL");
    const std::string account = m_cfg.getvalue("Database", "Account", "NULL");
    const std::string shard   = m_cfg.getvalue("Database", "Shard", "NULL");
    const std::string log     = m_cfg.getvalue("Database", "Log", "NULL");

    // --- Account DB ---
    if (__stringa(account).contains("NULL")) {
        return -1;
    }

    _snprintf(szConnStr, sizeof(szConnStr), connStrFormat, host.c_str(), user.c_str(), pass.c_str(),
              account.c_str());
    if (!m_dbPools[ACCOUNT].Initialize(szConnStr, m_dbMaxConn, m_dbMinConn)) {
        return -2;
    }

    m_dbInstancePool[ACCOUNT].Initialize(m_dbPools[ACCOUNT].GetConnection());

    // --- Shard DB ---
    if (__stringa(shard).contains("NULL")) {
        return -3;
    }

    _snprintf(szConnStr, sizeof(szConnStr), connStrFormat, host.c_str(), user.c_str(), pass.c_str(),
              shard.c_str());
    if (!m_dbPools[SHARD].Initialize(szConnStr, m_dbMaxConn, m_dbMinConn)) {
        return -4;
    }

    m_dbInstancePool[SHARD].Initialize(m_dbPools[SHARD].GetConnection());

    // --- Log DB ---
    if (__stringa(log).contains("NULL")) {
        return -5;
    }

    _snprintf(szConnStr, sizeof(szConnStr), connStrFormat, host.c_str(), user.c_str(), pass.c_str(),
              log.c_str());
    if (!m_dbPools[LOG].Initialize(szConnStr, m_dbMaxConn, m_dbMinConn)) {
        return -6;
    }

    m_dbInstancePool[LOG].Initialize(m_dbPools[LOG].GetConnection());

    return TRUE;
}

CDbInstance& CDbManager::GetInstance(DbType type)
{
    ACS_SCOPED_LOCK(m_cs);
    return m_dbInstancePool[type];
}

CDbConnection* CDbManager::GetConnection(DbType type)
{
    ACS_SCOPED_LOCK(m_cs);
    return m_dbPools[type].GetConnection();
}

void CDbManager::Release(DbType type, CDbConnection *pDbConn)
{
    ACS_SCOPED_LOCK(m_cs);
    m_dbPools[type].ReleaseConnection(pDbConn);
}