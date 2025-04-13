//
// Created by stenm on 29.03.2022.
//

#include <iostream>
#include <chrono>
#include "extensions/Logger.h"
#include <cstdlib>
#include <windows.h>

using namespace std;


// ===========================================================
// = STATIC VARIABLES:
// ===========================================================

HANDLE Logger::outHandle;
std::string Logger::LEVEL_NAME[] = {
    "[ERR]",
    "[WRN]",
    "[CRT]",
    "[INF]",
    "[DBG]"
};
ConsoleColor Logger::LEVEL_COLOR[] = {
    ConsoleColor::CC_RED,
    ConsoleColor::CC_YELLOW,
    ConsoleColor::CC_DARK_RED,
    ConsoleColor::CC_AQUA,
    ConsoleColor::CC_DARK_WHITE
};
std::vector<LogEntry> Logger::logMessages;

LogLevel Logger::minLogLevel = LOG_INFO;

// ===========================================================
// = CTOR:
// ===========================================================

Logger::Logger() {
    outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (outHandle == INVALID_HANDLE_VALUE) {
        cout << "Failed to get std output handle." << endl;
    }
}


// ===========================================================
// = Implementation:
// ===========================================================

void Logger::Log(const LogLevel& level, const string& msg) {
    if (level > minLogLevel) {
        return;
    }

    logMessages.push_back({level, msg});

    SetColor(LEVEL_COLOR[level]);
    cout << "[" << TimeStamp() << "] " << LEVEL_NAME[level] << ": " << msg << endl;
    ResetColor();
}

// ===========================================================

void Logger::Error(const string& msg) { Instance().Log(LOG_ERROR, msg); }
void Logger::Warn(const string& msg) { Instance().Log(LOG_WARNING, msg); }
void Logger::Critical(const string& msg) { Instance().Log(LOG_CRITICAL, msg); }
void Logger::Info(const string& msg) { Instance().Log(LOG_INFO, msg); }
void Logger::Debug(const string& msg) { Instance().Log(LOG_DEBUG, msg); }

// ===========================================================

std::string Logger::TimeStamp() {
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    //strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    strftime(buffer,sizeof(buffer),"%H:%M:%S",timeinfo);
    std::string str(buffer);
    return str;
}

// ===========================================================

void Logger::SetColor(const ConsoleColor& fg, const ConsoleColor& bg) {
    unsigned short consoleAttribute = (bg << 4) | fg;
    SetConsoleTextAttribute(outHandle, consoleAttribute);
}

// ===========================================================

void Logger::ResetColor() {
    SetColor(ConsoleColor::CC_GRAY, ConsoleColor::CC_BLACK);
}

// ===========================================================

void Logger::SetMinimumLogLevel(const LogLevel& logLevel) {
    minLogLevel = logLevel;
}