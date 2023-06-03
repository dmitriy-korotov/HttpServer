#pragma once
#ifndef RESPONSE_TEMPLATES_HPP
#define RESPONSE_TEMPLATES_HPP

#include <http/Defines.hpp>
#include <http/HttpTypes.hpp>



namespace http::response::templates
{
	std::string to_string(beast_http::status _status);
	response_t getBadResponse(const beast_http::status _status, const std::string& _server_name);
}

#endif // !RESPONSE_TEMPLATES_HPP
