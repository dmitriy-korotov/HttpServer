#pragma once

#include <string>
#include <unordered_map>



namespace util
{
	class key_value_parser
	{
	public:

		using parse_result = std::unordered_map<std::string, std::string>;



		key_value_parser(const key_value_parser&) = default;
		key_value_parser& operator=(key_value_parser&&) = default;

		key_value_parser() = default;
		key_value_parser(const std::string_view& _target, char _key_value_separator, char _pair_separator);

		void parse(const std::string_view& _target, char _key_value_separator, char _pair_separator);

		const parse_result& get() const noexcept;
		parse_result& get() noexcept;

	private:

		parse_result data_;

	};

	

	using KVparser = key_value_parser;
}