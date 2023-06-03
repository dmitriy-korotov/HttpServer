#pragma once
#ifndef TIME_HPP
#define TIME_HPP

#include <http/Defines.hpp>

#include <string>



namespace http::time
{
	std::string stringTimeNow() noexcept;
}

#endif // !TIME_HPP
