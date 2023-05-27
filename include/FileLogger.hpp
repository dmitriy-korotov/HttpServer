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



		enum class severity_level : uint8_t
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

		void log(std::string&& _message, severity_level _log_type) noexcept;

	private:

		bool createDirectory(const path& _path_to_log_directory) noexcept;

	private:

		static std::unordered_map<severity_level, std::string> string_view_severity_levels_;

	private:

		std::mutex mutex_;

		path path_to_log_file_;
		file file_to_log_;
		
	};
}

#endif // FILE_LOGGER_HPP