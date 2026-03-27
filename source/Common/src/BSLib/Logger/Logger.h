#pragma once

#include "RLUTIL.h"

class Logger {
public:
    static void info(const char *format, ...);
    static void info2(const char *format, ...);
    static void warn(const char *format, ...);
    static void warn2(const char *format, ...);
    static void error(const char *format, ...);
    static void error2(const char *format, ...);
    static void success(const char *format, ...);
    static void success2(const char *format, ...);

private:
    static void logwrite(int color, const char *format, va_list args);
};
