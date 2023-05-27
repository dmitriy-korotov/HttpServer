#pragma once
#ifndef URL_HPP
#define URL_HPP

#include "Defines.hpp"

#include <string>



namespace http::request::url
{
	std::string convertExtentionToContentType(const std::string_view& _extention);
}

#endif // !URL_HPP
