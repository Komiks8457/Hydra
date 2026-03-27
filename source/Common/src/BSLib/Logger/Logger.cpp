#include "Logger.h"
#include <cstdarg>
#include <ctime>

void Logger::info(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Logger::logwrite(rlutil::LIGHTCYAN, format, args);
    va_end(args);
}

void Logger::info2(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Logger::logwrite(rlutil::CYAN, format, args);
    va_end(args);
}

void Logger::warn(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Logger::logwrite(rlutil::LIGHTMAGENTA, format, args);
    va_end(args);
}

void Logger::warn2(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Logger::logwrite(rlutil::MAGENTA, format, args);
    va_end(args);
}

void Logger::error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Logger::logwrite(rlutil::LIGHTRED, format, args);
    va_end(args);
}

void Logger::error2(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Logger::logwrite(rlutil::RED, format, args);
    va_end(args);
}

void Logger::success(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Logger::logwrite(rlutil::LIGHTGREEN, format, args);
    va_end(args);
}

void Logger::success2(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    Logger::logwrite(rlutil::GREEN, format, args);
    va_end(args);
}

void Logger::logwrite(int color, const char *format, va_list args) {

    if (GetConsoleWindow() == NULL)
        return;

    std::time_t now = std::time(0);
    struct tm* tstruct = std::localtime(&now);
    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tstruct);

    char messageBuffer[1024];
    _vsnprintf(messageBuffer, sizeof(messageBuffer), format, args);

    rlutil::setColor(color);
    printf("[%s] %s\n", timeStr, messageBuffer);
    rlutil::setColor(rlutil::WHITE);

    fflush(stdout);
}
