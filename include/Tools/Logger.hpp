#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <string>
#include <iostream>
#include <utility>

namespace Tools {

	enum class LogLevel {
		Debug,    //调试信息
		Info,     //普通信息
		Key,      //关键信息
		Warning,  //警告信息
		Error,    //错误信息
	};

	class Logger {
	private:
		std::string m_moduleName;
		LogLevel m_currentLogLevel;

		std::string LevelToString();
		std::string GetCurrentTime();

		// 参数打印递归终止
		void LogArgs() {}

		// 递归打印任意参数
		template<typename T, typename... Args>
		void LogArgs(const T& first, Args&&... args) {
			std::cout << first;
			LogArgs(std::forward<Args>(args)...);
		}

		// 级别比较：是否允许打印
		bool IsLogEnable(LogLevel level) const {
			return static_cast<int>(level) >= static_cast<int>(m_currentLogLevel);
		}

		// 内部统一打印接口
		template<typename... Args>
		void PrintLog(LogLevel level, Args&&... args) {
			if (!IsLogEnable(level)) {
				return; // 级别不够，直接不打印
			}

			// 保存旧级别，临时设置
			LogLevel oldLevel = m_currentLogLevel;
			m_currentLogLevel = level;

			// 输出日志前缀
			std::cout << "[" << GetCurrentTime() << "] "
				<< "[" << LevelToString() << "] "
				<< "[" << m_moduleName << "] ";

			// 输出参数
			LogArgs(std::forward<Args>(args)...);
			std::cout << std::endl;

			// 恢复原级别
			m_currentLogLevel = oldLevel;
		}

	public:
		Logger();
		Logger(const std::string& moduleName, LogLevel level);
		~Logger();

		// 通用日志（使用当前级别）
		template<typename... Args>
		void Log(Args&&... args) {
			PrintLog(m_currentLogLevel, std::forward<Args>(args)...);
		}

		// 级别专用日志（带过滤）
		template <typename... Args>
		void DebugLog(Args&&... args) {
			PrintLog(LogLevel::Debug, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void InfoLog(Args&&... args) {
			PrintLog(LogLevel::Info, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void KeyLog(Args&&... args) {
			PrintLog(LogLevel::Key, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void WarningLog(Args&&... args) {
			PrintLog(LogLevel::Warning, std::forward<Args>(args)...);
		}

		template <typename... Args>
		void ErrorLog(Args&&... args) {
			PrintLog(LogLevel::Error, std::forward<Args>(args)...);
		}
	};

}

#endif
