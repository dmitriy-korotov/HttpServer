#include <http/QueryStringParser.hpp>

#include <boost/algorithm/string/replace.hpp>



namespace http::request::url
{
	query_string_parser::query_string_parser(const std::string_view& _target) noexcept
	{
		parse(_target);
	}



	void QSparser::parse(const std::string_view& _target)
	{
		std::string _replaced_target(_target);
		boost::algorithm::replace_all(_replaced_target, "%20", " ");

		size_t start_query_string = _replaced_target.find_first_of('?');
		if (start_query_string < _replaced_target.length())
		{
			key_value_parser::parse(_replaced_target.substr(start_query_string, _replaced_target.length() - start_query_string), '=', '&');
		}
	}
}