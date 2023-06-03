#pragma once

#include <boost/filesystem/path.hpp>

#include <fstream>
#include <optional>



namespace http
{
	using namespace boost::filesystem;



	class file_reader
	{
	public:

		file_reader() = default;
		file_reader(const path& _path);

		void read(const path& _path) const;
		std::string& read(const path& _path);

		std::string data() const noexcept;
		std::string& data() noexcept;

		void reset() noexcept;

	private:

		void __read_from_file(const path& _path) const;

	private:

		mutable std::mutex mutex_;

		std::optional<std::ifstream> file_;

		mutable std::string data_;

	};



	using freader = file_reader;
}