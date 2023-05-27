#pragma once
#ifndef REQUEST_HANDLE_HPP
#define REQUEST_HANDLE_HPP

#include "ResponseTypes.hpp"

#include <boost/beast/http/status.hpp>



namespace http::request
{
	namespace beast_http = boost::beast::http;



	bool isPathToFile(const std::string_view& _path);
	response::response_t getBadResponse(const beast_http::status _status, const std::string& _server_name);
	std::string conventExtentionToContentType(const std::string_view& _extention);
	std::string getTimeNow();
}

#endif // !REQUEST_HANDLE_HPP
