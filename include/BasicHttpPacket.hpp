#pragma once
#ifndef BASIC_HTTP_PACKET_HPP
#define BASIC_HTTP_PACKET_HPP

#include <boost/unordered_map.hpp>

#include <string>



namespace http
{
	class BasicHttpPacket
	{
	public:

		BasicHttpPacket(std::string&& _packet) noexcept;

		void parse(std::string&& _packet) noexcept;

	private:

		uint8_t m_major_http_version;
		uint8_t m_mainor_http_version;

		boost::unordered_map<std::string, std::string> m_other_headers;

		std::string m_body;

	};
}

#endif // BASIC_HTTP_PACKET_HPP
