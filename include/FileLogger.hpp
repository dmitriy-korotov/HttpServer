#pragma once
#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include "Defines.hpp"

#include <boost/filesystem/fstream.hpp>
#include <boost/noncopyable.hpp>

#include <unordered_map>



namespace http
{
	using namespace boost::filesystem;



	class file_logger : boost::noncopyable
	{
	public:

		using file = boost::filesystem::ofstream;



		enum class SeverityLevel : uint8_t
		{
			Debug,
			Info,
			Error,
			Fatal,
			Trace,
			Warning
		};



		file_logger(file_logger&&) = default;
		file_logger& operator=(file_logger&&) = default;

		file_logger(const std::string& _file_name_for_logger, const path& _path_to_log_directory) noexcept;
		~file_logger() = default;

		void log(std::string&& _message, SeverityLevel _log_type) noexcept;

	private:

		bool createDirectory(const path& _path_to_log_directory) noexcept;

	private:

		static std::unordered_map<SeverityLevel, std::string> m_string_view_sev_levels;

	private:

		path m_path_to_log_file;
		file m_file_to_log;
		
	};
}

#endif // FILE_LOGGER_HPP