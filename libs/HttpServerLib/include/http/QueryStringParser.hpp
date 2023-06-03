#pragma once

#include <string>
#include <unordered_map>



namespace http::request::url
{
	class query_string_parser
	{
	public:

		using query_string_t = std::unordered_map<std::string, std::string>;



		query_string_parser() = default;
		query_string_parser(const std::string_view& _target) noexcept;

		query_string_parser(query_string_parser&&) = default;
		query_string_parser& operator=(query_string_parser&&) = default;

		void parse(const std::string_view& _target);

		const query_string_t& get() const noexcept;
		query_string_t& get() noexcept;

	private:

		query_string_t query_string_;

	};



	using QSparser = query_string_parser;
}