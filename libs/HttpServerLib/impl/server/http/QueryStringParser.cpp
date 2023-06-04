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
		if (start_query_string < _target.length())
		{
			key_value_parser::parse(_target.substr(start_query_string + 1, _target.length() - start_query_string - 1), '=', '&');
		}
	}
}