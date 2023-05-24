#include "FileLogger.hpp"

#include <boost/filesystem/operations.hpp>

#include <cassert>
#include <iostream>



namespace http
{
	std::unordered_map<file_logger::SeverityLevel, std::string> file_logger::m_string_view_sev_levels = {
		{ file_logger::SeverityLevel::Debug,		"DEBUG" },
		{ file_logger::SeverityLevel::Error,		"ERROR" },
		{ file_logger::SeverityLevel::Fatal,		"FATAL" },
		{ file_logger::SeverityLevel::Info,			"INFO" },
		{ file_logger::SeverityLevel::Trace,		"TRACE" },
		{ file_logger::SeverityLevel::Warning,		"WARNING" }
	};



	file_logger::file_logger(const std::string& _file_name_for_logger, const path& _path_to_log_directory) noexcept
	{
		m_path_to_log_file = _path_to_log_directory / (_file_name_for_logger + ".log");
		if (!createDirectory(_path_to_log_directory))
		{
			std::cerr << "ERROR: file_logger: Can't create file: " << m_path_to_log_file << std::endl;
		}
	}



	bool file_logger::createDirectory(const path& _path_to_log_directory) noexcept
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



	void file_logger::log(std::string&& _message, SeverityLevel _log_type) noexcept
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
			std::cerr << "ERROR: file_logger: Can't open file: " << m_path_to_log_file << std::endl;
		}
	}
}