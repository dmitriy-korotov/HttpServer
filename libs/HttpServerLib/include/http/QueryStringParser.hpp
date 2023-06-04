#pragma once

#include <util/KeyValueParser.hpp>

#include <string>
#include <unordered_map>



namespace http::request::url
{
	class query_string_parser : public util::key_value_parser
	{
	public:

		using query_string_t = std::unordered_map<std::string, std::string>;



		query_string_parser() = default;
		query_string_parser(const std::string_view& _target) noexcept;

		query_string_parser(query_string_parser&&) = default;
		query_string_parser& operator=(query_string_parser&&) = default;

		void parse(const std::string_view& _target);

	private:

		using util::key_value_parser::parse;

	};



	using QSparser = query_string_parser;
}