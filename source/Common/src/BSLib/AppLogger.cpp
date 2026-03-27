#include "AppLogger.h"
#include "utils/MemoryUtility.h"
#include "stdext.h"

CAppLogger::pfnLogWriter CAppLogger::m_pfnLogWriter = NULL;
bool CAppLogger::m_Initialized = FALSE;

void CAppLogger::SetupHook(uintptr_t dwAddr)
{
    m_pfnLogWriter = (CAppLogger::pfnLogWriter)dwAddr;
    MEMUTIL_HOOK_FN(m_pfnLogWriter, addr_from_this(&CAppLogger::WriteLog))
}

char CAppLogger::WriteLog(E_LOG_MSG_TYPE type, const char* format, ...)
{
    char logmsg[8192];
    va_list ArgList;
    va_start(ArgList, format);
    _vsnprintf(logmsg, 8191, format, ArgList);
    va_end(ArgList);

    if (__stringa(logmsg).endswith("was initialized successfully") && !m_Initialized)
        m_Initialized = TRUE;

    return m_pfnLogWriter(type, logmsg);
}