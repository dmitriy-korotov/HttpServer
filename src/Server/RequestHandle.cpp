#include "RequestHandle.hpp"

#include <unordered_map>



namespace http::request
{
	static const std::unordered_map<std::string_view, std::string_view> extention_to_content_type_map_ =
	{
		{ "html",	"text/html" },
		{ "js",		"text/javascript" },
		{ "css",	"text/css" },
		{ "png",	"image/png" },
		{ "jpeg",	"image/jpeg" },
		{ "jpg",	"image/jpg" },
		{ "ico",	"image/ico" }
	};




	const std::string html = "<h>Page not found!</h>";




	bool isPathToFile(const std::string_view& _path)
	{
		return std::find(_path.begin(), _path.end(), '.') != _path.end();
	}



	response::response_t getBadResponse(const beast_http::status _status, const std::string& _server_name)
	{
		response::response_t _response;
		_response.result(_status);
		_response.keep_alive(false);
		_response.set(beast_http::field::server, _server_name);
		_response.set(beast_http::field::content_type, "text/html");
		_response.body() = html;
		_response.prepare_payload();
		return _response;
	}



	std::string conventExtentionToContentType(const std::string_view& _extention)
	{
		return std::string(extention_to_content_type_map_.at(_extention));
	}



	std::string getTimeNow()
	{
		auto time_now = std::chrono::system_clock::now();
		std::time_t _time = std::chrono::system_clock::to_time_t(time_now);
		return std::ctime(&_time);
	}
}