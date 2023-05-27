#pragma once
#ifndef RESPONSE_TYPES_HPP
#define RESPONSE_TYPES_HPP

#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/fields.hpp>



namespace http::response
{
	namespace beast_http = boost::beast::http;



	using alloc_t = std::allocator<char>;
	using body_t = beast_http::string_body;
	using fields_t = beast_http::basic_fields<alloc_t>;
	using request_t = beast_http::request<body_t, fields_t>;
	using response_t = beast_http::response<body_t, fields_t>;
}

#endif // !RESPONSE_TYPES_HPP
