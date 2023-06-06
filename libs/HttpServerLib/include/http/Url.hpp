#pragma once

#include <string>



namespace http::request::url
{
	bool isPathToSourceFile(const std::string_view& _target);
	std::string getEncodedUrl(const std::string_view& _target);
	std::string parseRelativePath(const std::string_view& _target);
}