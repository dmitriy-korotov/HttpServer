#include "FileLogger.hpp"

#include <boost/filesystem/operations.hpp>

#include <iostream>



namespace http
{
	std::unordered_map<file_logger::severity_level, std::string> file_logger::string_view_severity_levels_ = {
		{ file_logger::severity_level::Debug,		"DEBUG"   },
		{ file_logger::severity_level::Error,		"ERROR"   },
		{ file_logger::severity_level::Fatal,		"FATAL"   },
		{ file_logger::severity_level::Info,		"INFO"    },
		{ file_logger::severity_level::Trace,		"TRACE"   },
		{ file_logger::severity_level::Warning,		"WARNING" }
	};



	file_logger::file_logger(const std::string& _file_name_for_logger, const path& _path_to_log_directory) noexcept
	{
		path_to_log_file_ = _path_to_log_directory / (_file_name_for_logger + ".log");
		if (!createDirectory(_path_to_log_directory))
		{
			std::cerr << "ERROR: file_logger: Can't create file: " << path_to_log_file_ << std::endl;
		}
	}



	bool file_logger::createDirectory(const path& _path_to_log_directory) noexcept
	{
		boost::system::error_code _error;
		boost::filesystem::create_directories(_path_to_log_directory, _error);
		file_to_log_.open(path_to_log_file_, std::ios::out | std::ofstream::trunc);
		if (file_to_log_.is_open())
		{
			file_to_log_.close();
		}
		else
		{
			return false;
		}
		return !_error;
	}



	void file_logger::log(std::string&& _message, severity_level _log_type) noexcept
	{
		std::lock_guard<std::mutex> lock(mutex_);
		file_to_log_.open(path_to_log_file_, std::ios::app);
		if (file_to_log_.is_open())
		{
			auto time_point_now = std::chrono::system_clock::now();
			auto time = std::chrono::system_clock::to_time_t(time_point_now);
			file_to_log_ << string_view_severity_levels_[_log_type] << ":\t\t\t" << std::ctime(&time) << '\n' << _message << '\n';
			file_to_log_.close();
		}
		else
		{
			std::cerr << "ERROR: file_logger: Can't open file: " << path_to_log_file_ << std::endl;
		}
	}
}