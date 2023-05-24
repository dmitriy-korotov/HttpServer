#pragma once
#ifndef SESSION_HPP
#define SESSION_HPP

#include "Defines.hpp"

#include "FileLogger.hpp"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>



namespace http
{
	using namespace boost::filesystem;



	class session : public boost::enable_shared_from_this<session>, boost::noncopyable
	{
	public:

		using socket_t = boost::asio::ip::tcp::socket;
		using buffer_t = boost::asio::streambuf;



		session(session&&) = default;
		session& operator=(session&&) = default;

		session(socket_t&& _socket, file_logger& _logger);

		void start() noexcept;
		void close() noexcept;

		std::string info() const noexcept;

	private:

		void shedule_handle_of_request() noexcept;
		void shedule_responce(const std::string& _answer) noexcept;

	private:

		socket_t socket_;
		buffer_t stream_buffer_;

		file_logger& logger_;

	};
}

#endif // SESSION_HPP
