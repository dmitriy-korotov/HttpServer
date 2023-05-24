#include "Session.hpp"

#include <iostream>
#include <sstream>



namespace http
{
	session::session(socket_t&& _socket, file_logger& _logger)
			: socket_(std::move(_socket))
			, logger_(_logger)
	{ }



	void session::start() noexcept
	{
		shedule_handle_of_request();
	}



	std::string session::info() const noexcept
	{
		std::stringstream _info;
		_info << socket_.remote_endpoint();
		return _info.str();
	}



	void session::close() noexcept
	{
		socket_.close();
	}



	void session::shedule_handle_of_request() noexcept
	{
		boost::asio::async_read(socket_, stream_buffer_,
			[this](boost::system::error_code _error, std::size_t _bytes_transferred) -> void
			{
				if (_error)
				{
					logger_.log("Error recive request: " + _error.message(), file_logger::SeverityLevel::Error);
				}
			});
	}



	void session::shedule_responce(const std::string& _answer) noexcept
	{
		stream_buffer_.consume(stream_buffer_.size());
		stream_buffer_.sputn(_answer.c_str(), _answer.size());

		boost::asio::async_write(socket_, stream_buffer_,
			[this](boost::system::error_code _error, [[maybe_unused]] std::size_t) -> void
			{
				if (_error)
				{
					logger_.log("Error send response: " + _error.message(), file_logger::SeverityLevel::Error);
				}
			});
	}
}