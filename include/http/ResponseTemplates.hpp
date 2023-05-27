#pragma once
#ifndef RESPONSE_TEMPLATES_HPP
#define RESPONSE_TEMPLATES_HPP

#include "Defines.hpp"
#include "HttpTypes.hpp"



namespace http::response::templates
{
	response_t getBadResponse(const beast_http::status _status, const std::string& _server_name);
}

#endif // !RESPONSE_TEMPLATES_HPP
