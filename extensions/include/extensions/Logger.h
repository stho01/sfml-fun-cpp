#pragma once

#include <string>
#include <windows.h>
#include <vector>

enum LogLevel {
    LOG_ERROR = 0,
    LOG_CRITICAL = 1,
    LOG_WARNING = 2,
    LOG_INFO = 3,
    LOG_DEBUG = 4
};

enum ConsoleColor : unsigned int {
    CC_BLACK=0x00,
    CC_DARK_BLUE=0x1,
    CC_DARK_GREEN=0x2,
    CC_DARK_AQUA=0x3,
    CC_DARK_RED=0x4,
    CC_DARK_PURPLE=0x5,
    CC_DARK_YELLOW=0x6,
    CC_DARK_WHITE=0x7,
    CC_GRAY=0x8,
    CC_BLUE=0x9,
    CC_GREEN=0xA,
    CC_AQUA=0xB,
    CC_RED=0xC,
    CC_PURPLE=0xD,
    CC_YELLOW=0xE,
    CC_WHITE=0xF
};

struct LogEntry {
    LogLevel level;
    std::string message;
};

class Logger {
private:
    static std::string LEVEL_NAME[];
    static ConsoleColor LEVEL_COLOR[];
    static LogLevel minLogLevel;

public:
    static Logger Instance() {
        static Logger l;

        return l;
    }

    static void SetMinimumLogLevel(const LogLevel& logLevel);

    void Log(const LogLevel& level, const std::string& msg);
    static void Error(const std::string& msg);
    static void Warn(const std::string& msg);
    static void Critical(const std::string& msg);
    static void Info(const std::string& msg);
    static void Debug(const std::string& msg);

private:
    Logger();
    static void SetColor(const ConsoleColor& fg, const ConsoleColor& bg = ConsoleColor::CC_BLACK);
    static void ResetColor();

private:
    static std::string TimeStamp();
    static HANDLE outHandle;
    static std::vector<LogEntry> logMessages;

};
