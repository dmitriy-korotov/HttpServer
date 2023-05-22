#pragma once
#ifndef SESSION_HPP
#define SESSION_HPP

#include "Defines.hpp"

#include "FileLogger.hpp"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>



namespace http
{
	class Session : public boost::enable_shared_from_this<Session>
	{
	public:

		using socket_t = boost::asio::ip::tcp::socket;
		using buffer_t = boost::asio::streambuf;



		Session(const Session&) = delete;
		Session& operator=(const Session&) = delete;

		Session(Session&&) = default;
		Session& operator=(Session&&) = default;
		~Session() = default;

		Session(socket_t&& _socket, const std::string& _path_to_log_directory);

		void start() noexcept;
		std::string info() const noexcept;
		void close() noexcept;

	private:

		void async_request_handler() noexcept;
		void async_responce_handler(const std::string& _answer) noexcept;

	private:

		socket_t m_socket;
		buffer_t m_stream_buffer;

		//FileLogger m_logger;

	};
}

#endif // SESSION_HPP
