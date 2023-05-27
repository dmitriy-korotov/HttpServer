#include "http/Url.hpp"

#include <unordered_map>



namespace http::request::url
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



	std::string convertExtentionToContentType(const std::string_view& _extention)
	{
		return std::string(extention_to_content_type_map_.at(_extention));
	}
}