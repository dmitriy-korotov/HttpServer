#include <webcpp/http/QueryStringParser.hpp>

#include <webcpp/http/Url.hpp>

#include <boost/algorithm/string/replace.hpp>

#include <iostream>


namespace http::request::url
{
	query_string_parser::query_string_parser(const std::string_view& _target) noexcept
	{
		parse(_target);
	}



	void QSparser::parse(const std::string_view& _target)
	{
		std::string _replaced_target = http::request::url::getEncodedUrl(_target);
		
		size_t start_query_string = _replaced_target.find_first_of('?');
		if (start_query_string != std::string::npos)
		{
			key_value_parser::parse(_replaced_target.substr(start_query_string + 1, _replaced_target.length() - start_query_string - 1), '=', '&');
		}
	}
}