#include "FileLogger.hpp"

#include <boost/filesystem/operations.hpp>

#include <cassert>
#include <iostream>



namespace http
{
	boost::unordered_map<FileLogger::SeverityLevel, std::string> FileLogger::m_string_view_sev_levels = {
		{ FileLogger::SeverityLevel::Debug,		"DEBUG" },
		{ FileLogger::SeverityLevel::Error,		"ERROR" },
		{ FileLogger::SeverityLevel::Fatal,		"FATAL" },
		{ FileLogger::SeverityLevel::Info,		"INFO" },
		{ FileLogger::SeverityLevel::Trace,		"TRACE" },
		{ FileLogger::SeverityLevel::Warning,	"WARNING" }
	};



	FileLogger::FileLogger(const std::string& _file_name_for_logger, const std::string& _path_to_log_directory) noexcept
	{
		m_path_to_log_file = _path_to_log_directory + '/' + _file_name_for_logger + ".log";
		if (!createFile(_file_name_for_logger, _path_to_log_directory))
		{
			std::cerr << "ERROR: Can't create file: " << m_path_to_log_file << std::endl;
		}
	}



	bool FileLogger::createFile(const std::string& _file_name_for_logger, const std::string& _path_to_log_directory) noexcept
	{
		boost::system::error_code _error;
		boost::filesystem::create_directories(_path_to_log_directory, _error);
		m_file_to_log.open(m_path_to_log_file, std::ios::out | std::ofstream::trunc);
		if (m_file_to_log.is_open())
		{
			m_file_to_log.close();
		}
		else
		{
			return false;
		}
		return !_error;
	}



	void FileLogger::log(std::string&& _message, SeverityLevel _log_type) noexcept
	{
		m_file_to_log.open(m_path_to_log_file, std::ios::app);
		if (m_file_to_log.is_open())
		{
			auto time_point_now = std::chrono::system_clock::now();
			auto time = std::chrono::system_clock::to_time_t(time_point_now);
			m_file_to_log << m_string_view_sev_levels[_log_type] << ": " << _message << "\t\t\t" << std::ctime(&time) << '\n';
			m_file_to_log.close();
		}
		else
		{
			std::cerr << "ERROR: Can't open file: " << m_path_to_log_file << std::endl;
		}
	}
}