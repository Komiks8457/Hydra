#pragma once

#include "pch.h"

#define PutLog(type, fmt, ...) \
    CAppLogger::WriteLog(type, fmt, ##__VA_ARGS__)

#define IS_READY_STATE \
    CAppLogger::Initialized()

enum E_LOG_MSG_TYPE
{
    NORMAL      = 0x0000000,
    WARNING     = 0x1000000,
    FATAL       = 0x2000001,
    PERFORMANCE = 0x3000001
};

class CAppLogger {
public:
    static void SetupHook(uintptr_t dwAddr);
    static char WriteLog(E_LOG_MSG_TYPE Type, const char* format, ...);
    static bool Initialized() { return m_Initialized; }

private:
    typedef char (__cdecl* pfnLogWriter)(int, LPCSTR);
    static pfnLogWriter m_pfnLogWriter;
    static bool m_Initialized;
};
