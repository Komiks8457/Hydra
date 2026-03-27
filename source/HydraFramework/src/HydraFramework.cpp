#include "HydraFramework.h"
#include "BSLib/AppLogger.h"
#include "BSLib/NetEngine/NetEngine.h"
#include "utils/MemoryUtility.h"
#include "version.h"

///////////////////////////////////////////////////////////
// GlobalData

namespace GlobalData
{
    char        SecretKey[21] = "sn0wd3n.n2h-oqm7n.ap";
    uint16_t    CustomMsgID[] = { 0x623D };
}

///////////////////////////////////////////////////////////
// HydraFramework

template<> HydraFramework::CMainProcess* CSingletonT<HydraFramework::CMainProcess>::s_pObject = NULL;

namespace HydraFramework
{
    void InitTask(void *ptr)
    {
        DWORD netengine = MEMUTIL_ADD_PTR(ptr, 0x14C);

        while (!g_pNetEngine && !IS_READY_STATE) {
            CNetEngine::Initialize(netengine);
            Sleep(50);
        }

        Logger::warn2("g_pNetEngine = CNetEngine instance (0x%p)", g_pNetEngine);
    }

    void CustomMsgHandler(void* ptr)
    {
        ACS_SCOPED_LOCK(g_pHydraMainProcess->GetCS());

        CMsg *pMsg = static_cast<CMsg*>(ptr);

        if (pMsg)
        {
            WORD  wMsgID = pMsg->GetMsgID();
            DWORD dwSessionID = pMsg->GetSessionID();

            switch (wMsgID)
            {
                case 0x623D: {
                    switch (pMsg->ReadUInt8())
                    {
                        case 0x1: {
                            SessionInfo sessInfo;
                            pMsg->Read<SessionInfo>(sessInfo);
                            g_pHydraMainProcess->AddSessionID(dwSessionID, sessInfo);
                            //pMsg->PrintDumpData(__FUNCTION__);
                            break;
                        }
                    }
                    break;
                }
                default: PutLog(FATAL, "Unhandled msg id (0x%X)", wMsgID);
            }

            pMsg->ResetPos();
            DELMSG(pMsg);
        }
    }

    void DoWork(void* ptr)
    {
        CMsg *pMsg = static_cast<CMsg*>(ptr);

        if (pMsg)
        {
            WORD  wMsgID = pMsg->GetMsgID();
            DWORD dwMsgSize = pMsg->GetMsgSize();
            DWORD dwSessionID = pMsg->GetSessionID();

            switch (wMsgID)
            {
                case 0x1002: {
                    g_pHydraMainProcess->DelSessionID(dwSessionID);
                    break;
                }
                case 0x600D: {
                    if (dwMsgSize > 1000)
                    {
                        BYTE b1 = NULL, b2 = NULL, b3 = NULL, b4 = NULL;

                        pMsg->Read<BYTE>(b1);
                        pMsg->Read<BYTE>(b2);
                        pMsg->Read<BYTE>(b3);
                        pMsg->Read<BYTE>(b4);

                        if (b1 == 0 && b2 == 1 && b3 == 3 && b4 == 4)
                        {
                            db_map_t local_db_map;

                            pMsg->SetRdPos(0x24D);
                            local_db_map[ACCOUNT] = pMsg->ReadStringA();

                            pMsg->SetRdPos(0x443);
                            local_db_map[SHARD] = pMsg->ReadStringA();

                            pMsg->SetRdPos(0x4A6);
                            local_db_map[LOG] = pMsg->ReadStringA();

                            if (!local_db_map.empty()) {
                                g_pHydraMainProcess->SetConnectionString(local_db_map);
                            } else {
                                Logger::error2("Failed to get database connection string.");
                            }
                        }
                    }

                    break;
                }
            }

            //pMsg->PrintDumpData(__FUNCTION__);
            pMsg->ResetPos();
            DELMSG(pMsg);
        }
    }

    CMainProcess::CMainProcess(void* ptr, const char* className) : m_version(BUILD_REVISION_STRING)
    {
        m_threadPool = new CThreadPool(5);
        m_threadPool->EnqueueTask(InitTask, ptr);

        ClassEntry entry;
        entry.pointer = ptr;
        entry.name = className;
        m_className.push_back(entry);
    }

    CMainProcess::~CMainProcess()
    {
        delete m_threadPool;
    }

    const std::string CMainProcess::GetModuleName(void* ptr)
    {
        ACS_SCOPED_LOCK(m_cs);

        for (std::vector<ClassEntry>::const_iterator it = m_className.begin(); it != m_className.end(); ++it)
            if (it->pointer == ptr) return it->name;

        return "UNKNOWN";
    }

    void *CMainProcess::GetModuleInstance(const char *moduleName)
    {
        ACS_SCOPED_LOCK(m_cs);

        for (std::vector<ClassEntry>::const_iterator it = m_className.begin(); it != m_className.end(); ++it)
            if (it->name == moduleName) return it->pointer;

        return NULL;
    }

    void CMainProcess::HandleCustomMsg(CMsg* pMsg)
    {
        ACS_SCOPED_LOCK(m_cs);

        if (!pMsg) return;

        while (!g_pNetEngine)
        {
            Sleep(10);
            continue;
        }

        WORD  wMsgID = pMsg->GetMsgID();
        DWORD dwTotalSize = pMsg->GetMsgSize();
        DWORD dwSessionID = pMsg->GetSessionID();

        CMsg* pMsgCopy = NEWMSG(wMsgID, FALSE);

        if (pMsgCopy)
        {
            if (dwTotalSize > pMsgCopy->GetCapacity())
                pMsgCopy->Resize(dwTotalSize);

            ::memcpy(pMsgCopy->GetBufferAt(0), pMsg->GetBufferAt(0), dwTotalSize);

            pMsgCopy->SetSessionID(dwSessionID);
            pMsgCopy->ResetPos();

            //m_threadPool->EnqueueTask(CustomMsgHandler, pMsgCopy);
        }

        pMsg->ResetPos();
    }

    void CMainProcess::HandleMsg(CMsg* pMsg)
    {
        ACS_SCOPED_LOCK(m_cs);

        while (!g_pNetEngine)
        {
            Sleep(10);
            continue;
        }

        WORD  wMsgID = pMsg->GetMsgID();
        DWORD totalBytes = pMsg->GetMsgSize();
        DWORD sessionID = pMsg->GetSessionID();

        CMsg* pMsgCopy = NEWMSG(wMsgID, FALSE);

        if (pMsgCopy)
        {
            if (totalBytes > pMsgCopy->GetCapacity())
                pMsgCopy->Resize(totalBytes);

            ::memcpy(pMsgCopy->GetBufferAt(0), pMsg->GetBufferAt(0), totalBytes);

            pMsgCopy->SetSessionID(sessionID);
            pMsgCopy->ResetPos();

            m_threadPool->EnqueueTask(DoWork, pMsgCopy);
        }

        pMsg->ResetPos();
    }

    void CMainProcess::SetConnectionString(const db_map_t &newMap)
    {
        ACS_SCOPED_LOCK(m_cs);

        m_db = newMap;
    }

    std::string CMainProcess::GetConnectionString(DB dbType)
    {
        ACS_SCOPED_LOCK(m_cs);

        if (m_db.count(dbType))
            return m_db[dbType];
        return "";
    }

    DWORD CMainProcess::GetSessionID(const std::string &module)
    {
        ACS_SCOPED_LOCK(m_cs);

        for (session_map_t::iterator it = m_sessions.begin(); it != m_sessions.end();)
        {
            if (it->second.szName == module)
            {
                return it->first;
            }
            else ++it;
        }

        return NULL;
    }

    void CMainProcess::AddSessionID(DWORD dwSessionID, SessionInfo &sessInfo)
    {
        ACS_SCOPED_LOCK(m_cs);

        m_sessions[dwSessionID] = sessInfo;
        PutLog(WARNING, "Added %s(%d)", sessInfo.szName.c_str(), dwSessionID);
    }

    void CMainProcess::DelSessionID(DWORD dwSessionID)
    {
        ACS_SCOPED_LOCK(m_cs);

        for (session_map_t::iterator it = m_sessions.begin(); it != m_sessions.end();)
        {
            if (it->first == dwSessionID)
            {
                PutLog(WARNING, "Removed %s(%d)", it->second.szName.c_str(), it->first);
                m_sessions.erase(it++);
                break;
            }
            else ++it;
        }
    }
}
