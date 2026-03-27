#include "../../include/Tools/Logger.hpp"
#include <chrono>
#include <ctime>

namespace Tools {

	Logger::Logger() {
		m_moduleName = "Default";
		m_currentLogLevel = LogLevel::Info;
	}

	Logger::Logger(const std::string& moduleName, LogLevel level) {
		m_moduleName = moduleName;
		m_currentLogLevel = level;
	}

	Logger::~Logger() = default;

	std::string Logger::LevelToString() {
		switch (m_currentLogLevel) {
			case LogLevel::Debug:   return "DEBUG";
			case LogLevel::Info:    return "INFO";
			case LogLevel::Key:     return "KEY";
			case LogLevel::Warning: return "WARNING";
			case LogLevel::Error:   return "ERROR";
			default:                return "UNKNOWN";
		}
	}

	std::string Logger::GetCurrentTime() {
		auto now = std::chrono::system_clock::now();
		time_t now_time = std::chrono::system_clock::to_time_t(now);
		tm local_tm = *localtime(&now_time);

		char buf[64];
		strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);
		return std::string(buf);
	}

}
