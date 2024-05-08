#include "LoggerSafe.h"
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

namespace Log
{
	void LoggerSafe::Init(std::string_view log_file_name)
	{
		if (log_file_name.empty())
		{
			throw std::invalid_argument("Log file name is empty");
		}

		m_LogFile.open(log_file_name.data(), std::ios::out | std::ios::app);
		if (!m_LogFile.is_open())
		{
			throw std::runtime_error("Can't open log file");
		}
	}

	void LoggerSafe::Cleanup() noexcept
	{
		if (m_LogFile.is_open())
		{
			m_LogFile.close();
		}
	}

	void LoggerSafe::LogInformation(std::string_view log)
	{
		Log(LogType::Information, log);
	}

#ifdef _DEBUG
	void LoggerSafe::LogDebug(std::string_view log)
	{
		Log(LogType::Debug, log);
	}
#endif // _DEBUG

	void LoggerSafe::LogWarning(std::string_view log)
	{
		Log(LogType::Warning, log);
	}

	void LoggerSafe::LogError(std::string_view log)
	{
		Log(LogType::Error, log);
	}

	void LoggerSafe::Log(LogType type, std::string_view log)
	{
		auto get_color_by_type = [](LogType type) noexcept
		{
#ifdef _DEBUG
			if (type == LogType::Debug)
			{
				return "\033[35m"; // purple
			}
#endif // _DEBUG
			if (type == LogType::Warning)
			{
				return "\033[33m"; // yellow
			}
			if (type == LogType::Error)
			{
				return "\033[31m"; // red
			}

			return "\033[0m"; // reset color (white)
		};

		auto get_description_by_type = [](LogType type) noexcept
		{
#ifdef _DEBUG
			if (type == LogType::Debug)
			{
				return "Debug";
			}
#endif // _DEBUG
			if (type == LogType::Warning)
			{
				return "Warning";
			}
			if (type == LogType::Error)
			{
				return "Error";
			}

			return "Info";
		};

		auto get_current_date_time = []() noexcept
		{
			using namespace std::chrono;

			const auto now{ system_clock::to_time_t(system_clock::now()) };

			std::tm tm_buf{};

#ifdef _WIN32
			localtime_s(&tm_buf, &now);
#else
			localtime_r(&now, &tm_buf);
#endif // endif _WIN32

			std::stringstream ss;
			ss << std::put_time(&tm_buf, "%d-%m-%Y %H:%M:%S");

			return ss.str();
		};

		if (log.empty())
		{
			throw std::invalid_argument("Log record is empty");
		}

		if (!m_LogFile.is_open())
		{
			throw std::runtime_error("The log file was not opened");
		}

		std::string log_record;
		log_record += "[";
		log_record += get_current_date_time();
		log_record += "] (";
		log_record += get_description_by_type(type);
		log_record += ") ";
		log_record += log;
		log_record += "\n";

		std::unique_lock lock(m_Mutex);
		m_LogFile << log_record;
		m_LogFile.flush();
		std::cout << get_color_by_type(type) << log_record << get_color_by_type(LogType::Information);
	}
}
