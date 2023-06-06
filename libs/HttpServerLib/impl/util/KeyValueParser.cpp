#include <util/KeyValueParser.hpp>



namespace util
{
	key_value_parser::key_value_parser(const std::string_view& _target, char _key_value_separator, char _pair_separator)
	{
		parse(_target, _key_value_separator, _pair_separator);
	}



	void key_value_parser::parse(const std::string_view& _target, char _key_value_separator, char _pair_separator)
	{
		size_t start = 0;
		while (start < _target.length())
		{
			size_t sep = _target.find_first_of(_key_value_separator, start);
			if (sep == std::string::npos)
			{
				return;
			}
			size_t finded_end_key_value = _target.find_first_of(_pair_separator, sep);
			size_t end = finded_end_key_value != std::string::npos ? finded_end_key_value : _target.length();

			data_.emplace(
				_target.substr(start, sep - start),
				_target.substr(sep + 1, end - sep - 1));

			start = end + 1;
		}
	}



	const key_value_parser::parse_result& key_value_parser::get() const noexcept
	{
		return data_;
	}



	key_value_parser::parse_result& key_value_parser::get() noexcept
	{
		return data_;
	}
}