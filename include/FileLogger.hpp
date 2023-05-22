#pragma once
#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include "Defines.hpp"

#include <boost/unordered_map.hpp>
#include <boost/filesystem/fstream.hpp>



namespace http
{
	class FileLogger
	{
	public:

		using File = boost::filesystem::ofstream;



		enum class SeverityLevel : uint8_t
		{
			Debug,
			Info,
			Error,
			Fatal,
			Trace,
			Warning
		};



		FileLogger(const FileLogger&) = delete;
		FileLogger& operator=(const FileLogger&) = delete;

		FileLogger(FileLogger&&) = default;
		FileLogger& operator=(FileLogger&&) = default;

		FileLogger(const std::string& _file_name_for_logger, const std::string& _path_to_log_directory) noexcept;
		~FileLogger() = default;

		void log(std::string&& _message, SeverityLevel _log_type) noexcept;

	private:

		bool createFile(const std::string& _file_name_for_logger, const std::string& _path_to_log_directory) noexcept;

	private:

		static boost::unordered_map<SeverityLevel, std::string> m_string_view_sev_levels;

	private:

		std::string m_path_to_log_file;
		File m_file_to_log;
		
	};
}

#endif // FILE_LOGGER_HPP