#pragma once

#include <webcpp/http/Defines.hpp>
#include <webcpp/http/HttpTypes.hpp>

#include <boost/filesystem/path.hpp>

#include <string>



namespace http::response
{
	namespace beast_http = boost::beast::http;



	enum class EResponseContentType : uint8_t
	{
		Plain,
		HTML,
		JSON,
		XML
	};



	response_t createResponse(std::string&& _string_response);
	response_t createResponseHTML(std::string&& _string_response);
	response_t renderTemplate(const boost::filesystem::path& _path);
	response_t createResponseJSON(std::string&& _string_response);
	response_t createResponseXML(std::string&& _string_response);
}