#include "Session.hpp"

#include <iostream>
#include <sstream>



namespace http
{
	Session::Session(socket_t&& _socket, const std::string& _path_to_log_directory)
			: m_socket(std::move(_socket))
			//, m_logger("Session: " + m_socket.remote_endpoint().address().to_string(), _path_to_log_directory)
	{ }



	void Session::start() noexcept
	{
		async_request_handler();
	}



	std::string Session::info() const noexcept
	{
		std::stringstream _sstring;
		_sstring << m_socket.remote_endpoint();
		return _sstring.str();
	}



	void Session::close() noexcept
	{
		m_socket.close();
	}



	void Session::async_request_handler() noexcept 
	{
		boost::asio::async_read_until(m_socket, m_stream_buffer, '\n',
			[self = shared_from_this()](boost::system::error_code _error, std::size_t _bytes_transferred) -> void
			{
				std::string answer = "HTTP/1.1 200 OK\n\r"
									 "Content-Encoding: identity\n\r"
									 "Content-Type: text/plan; charset=utf-8\n\r"
									 "Connection: close\r\n"
									 "Content-Length: 43\n\r\n\r"
									 "<!DOCTYPE html>\n\r"
									 "<h>Hello World</h>";

				std::string answer2 = "HTTP/1.1 200 OK\n\r"
					"Content-Type: text/plain\n\r"
					"Transfer-Encoding: chunked\n\r\n\r"

					"7\r\n"
					"Mozilla\r\n"
					"11\r\n"
					"Developer Network\r\n"
					"0\r\n"
					"\r\n";

				self->async_responce_handler(std::move(answer));
			});
	}



	void Session::async_responce_handler(const std::string& _answer) noexcept
	{
		m_stream_buffer.consume(m_stream_buffer.size());
		m_stream_buffer.sputn(_answer.c_str(), _answer.size());

		

		boost::asio::async_write(m_socket, m_stream_buffer,
			[self = shared_from_this()](boost::system::error_code _error, std::size_t _bytes_transferred) -> void
			{

				if (_error)
				{
					std::cerr << _error.message() << std::endl;
				}
			});
	}
}