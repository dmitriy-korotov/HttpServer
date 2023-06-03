#include <system/FileReader.hpp>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>



namespace http
{
	file_reader::file_reader(const path& _path)
	{
		read(_path);
	}

	void file_reader::read(const path& _path) const
	{
		__read_from_file(_path);
	}

	std::string& file_reader::read(const path& _path)
	{
		__read_from_file(_path);
		return data_;
	}

	std::string file_reader::data() const noexcept
	{
		return data_;
	}

	std::string& file_reader::data() noexcept
	{
		return data_;
	}

	void file_reader::reset() noexcept
	{
		std::lock_guard<std::mutex> lock(mutex_);
		data_.clear();
	}

	void file_reader::__read_from_file(const path& _path) const
	{
		std::lock_guard<std::mutex> lock(mutex_);

		boost::interprocess::mode_t mode = boost::interprocess::mode_t::read_only;
		boost::interprocess::file_mapping file_(_path.c_str(), mode);

		boost::interprocess::mapped_region region(file_, mode, 0, 0);

		const char* file_position = static_cast<const char*>(region.get_address());

		data_.append(file_position, region.get_size());
	}
}