#pragma once
#ifndef URL_HPP
#define URL_HPP

#include "Defines.hpp"

#include <string>



namespace http::request::url
{
	bool isPathToSourceFile(const std::string_view& _target);

	std::string convertExtentionToContentType(const std::string_view& _extention);
	
	std::string parseRelativePath(const std::string_view& _target);
}

#endif // !URL_HPP
