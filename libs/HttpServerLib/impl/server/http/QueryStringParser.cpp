#include <http/QueryStringParser.hpp>



namespace http::request::url
{
	query_string_parser::query_string_parser(const std::string_view& _target) noexcept
	{
		parse(_target);
	}



	void QSparser::parse(const std::string_view& _target)
	{
		size_t start_query_string = _target.find_first_of('?');
		while (start_query_string < _target.length())
		{
			size_t sep = _target.find_first_of('=', start_query_string);
			if (sep < _target.length())
			{
				size_t finded_end_key_value = _target.find_first_of('&', sep);
				size_t end = finded_end_key_value < _target.length() ? finded_end_key_value : _target.length();
				
				query_string_.emplace(
					_target.substr(start_query_string + 1, sep - start_query_string - 1),
					_target.substr(sep + 1, end - sep - 1));
				
				start_query_string = end;
			}
		}
	}



	const QSparser::query_string_t& QSparser::get() const noexcept
	{
		return query_string_;
	}



	QSparser::query_string_t& QSparser::get() noexcept
	{
		return query_string_;
	}
}