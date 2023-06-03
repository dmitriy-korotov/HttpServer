#include <system/Time.hpp>

#include <chrono>



namespace http::time
{
	std::string stringTimeNow() noexcept
	{
		auto time_now = std::chrono::system_clock::now();
		std::time_t _time = std::chrono::system_clock::to_time_t(time_now);
		return std::ctime(&_time);
	}
}