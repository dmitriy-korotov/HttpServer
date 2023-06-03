#pragma once

#include <http/Defines.hpp>
#include <http/HttpTypes.hpp>



namespace http::response::templates
{
	std::string to_string(beast_http::status _status);
	boost_response_t getBadResponse(const beast_http::status _status, const std::string& _server_name);
}