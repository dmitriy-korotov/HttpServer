#pragma once

#include <http/Request_fwd.hpp>
#include <http/Response_fwd.hpp>

#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/fields.hpp>



namespace http
{
	namespace beast_http = boost::beast::http;
	
	using alloc_t = std::allocator<std::byte>;
	using body_t = beast_http::string_body;
	using fields_t = beast_http::basic_fields<alloc_t>;
	using boost_request_t = beast_http::request<body_t, fields_t>;
	using boost_response_t = beast_http::response<body_t, fields_t>;
	using request_t = http::Request<body_t, fields_t>;
	using response_t = http::Response<body_t, fields_t>;
}