#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <memory>
#include <ctime>

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
private:
    Logger() = default;
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string getLevelString(LogLevel level);
    std::string getCurrentTime();

public:
    static Logger& getInstance();
    void setLogFile(const std::string& filename);
    void log(const std::string& message, LogLevel level = LogLevel::Info);

private:
    std::ofstream logFile_;
    std::mutex mutex_;
};