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





	bool isPathToSourceFile(const std::string_view& _target)
	{
		return (_target.find_last_of('.') < _target.size());
	}



	std::string convertExtentionToContentType(const std::string_view& _extention)
	{
		return std::string(extention_to_content_type_map_.at(_extention));
	}



	std::string parseRelativePath(const std::string_view& _target)
	{
		size_t question_position = _target.find_first_of('?');
		return (question_position < _target.length()) ? std::string(_target.substr(0, question_position)) : std::string(_target);
	}
}