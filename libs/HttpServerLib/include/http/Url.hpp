#pragma once

#include <string>



namespace http::request::url
{
	bool isPathToSourceFile(const std::string_view& _target);

	std::string convertExtentionToContentType(const std::string_view& _extention);
	
	std::string parseRelativePath(const std::string_view& _target);
}