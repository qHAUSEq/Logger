#include "Logger.h"

Logger::~Logger() {
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

std::string Logger::getLevelString(LogLevel level) {
    switch (level) {
    case LogLevel::Info:    return "INFO";
    case LogLevel::Warning: return "WARNING";
    case LogLevel::Error:   return "ERROR";
    default:                return "UNKNOWN";
    }
}
std::string Logger::getCurrentTime() {
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mutex_);
    logFile_.open(filename, std::ios::out | std::ios::app);
    if (!logFile_.is_open()) {
        std::cerr << "Can't open log-file: " << filename << std::endl;
    }
}

void Logger::log(const std::string& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (logFile_.is_open()) {
        logFile_ << getCurrentTime() << " [" << getLevelString(level) << "] " << message << std::endl;
    }
    else {
        std::cerr << "Logger not init. Message: " << message << std::endl;
    }
}
