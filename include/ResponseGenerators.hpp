#pragma once
#ifndef PRESPONSE_GENERATORS_HPP
#define PRESPONSE_GENERATORS_HPP

#include "ResponseTypes.hpp"

#include <boost/filesystem/path.hpp>

#include <string>



namespace http::response
{
	namespace beast_http = boost::beast::http;



	enum class EResponseFormat : uint8_t
	{
		Plain,
		HTML,
		JSON,
		XML
	};



	response_t sendResponse(std::string&& _string_response);
	response_t sendResponseHTML(std::string&& _string_response);
	response_t templateRender(const boost::filesystem::path& _path);
	response_t sendResponseJSON(std::string&& _string_response);
	response_t sendResponseXML(std::string&& _string_response);
}

#endif // !PRESPONSE_GENERATORS_HPP
