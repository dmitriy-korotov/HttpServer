#include "Session.hpp"

#include "FileReader.hpp"
#include "RequestHandle.hpp"
#include "SessionManager.hpp"
#include "HttpServer.hpp"

#include <boost/beast/http/read.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/status.hpp>

#include <iostream>
#include <sstream>



static constexpr uint8_t REQUEST_DEADLINE_TIME = 10;
static constexpr std::string_view SERVER_NAME = "Dmitriy.Korotov";



namespace http
{
	response_t session::request_handler(const request_t& _request) const noexcept try
	{
		response_t response_;
		response_.keep_alive(false);

		if (_request.method() == beast_http::verb::get)
		{
			std::string _target = _request.target();
			if (request::isPathToFile(_target))
			{
				size_t position_point_before_extention = _target.find_last_of('.') + 1;
				std::string extention = _target.substr(position_point_before_extention, _target.length() - position_point_before_extention);
				response_.set(beast_http::field::content_type, request::conventExtentionToContentType(extention));

				file_reader file_reader_(_target);
				response_.body() = std::move(file_reader_.data());
			}
			else
			{
				auto handler_it = server_.URL_handlres_map_.find(_target);
				if (handler_it == server_.URL_handlres_map_.end())
				{
					return request::getBadResponse(beast_http::status::not_found, SERVER_NAME.data());
				}
				response_ = handler_it->second(_request);
			}
		}
		response_.result(beast_http::status::ok);
		response_.set(beast_http::field::server, SERVER_NAME.data());
		response_.set(beast_http::field::accept_datetime, request::getTimeNow());
		response_.prepare_payload();

		return response_;
	}
	catch (const std::exception& _ex)
	{
		return request::getBadResponse(beast_http::status::bad_gateway, SERVER_NAME.data());
	}





	session::session(socket_t&& _socket, http_server& _server, session_manager& _session_manager, file_logger& _logger)
			: socket_(std::move(_socket))
			, server_(_server)
			, session_manager_(_session_manager)
			, logger_(_logger)
	{ }



	void session::start() noexcept
	{
		check_deadline();
		shedule_handle_of_request();
	}



	std::string session::info() const noexcept try
	{
		std::stringstream _info;
		_info << socket_.remote_endpoint();
		return _info.str();
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Can't get info about seession: " + std::string(_ex.what()), file_logger::severity_level::Error);
		return {};
	}



	void session::close() noexcept
	{
		boost::system::error_code _error;
		socket_.close(_error);
		if (_error)
		{
			logger_.log("Closing error: " + _error.message(), file_logger::severity_level::Error);
		}
	}



	void session::check_deadline() try
	{
		if (request_deadline_.expiry() <= std::chrono::steady_clock::now())
		{
			session_manager_.closeSession(shared_from_this());
			return;
		}

		request_deadline_.expires_after(std::chrono::seconds(REQUEST_DEADLINE_TIME));

		request_deadline_.async_wait(
			[this](boost::system::error_code _error)
			{
				if (_error)
				{
					logger_.log("Deadline error: " + _error.message(), file_logger::severity_level::Error);
				}
				check_deadline();
			});
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Deadline error: " + std::string(_ex.what()), file_logger::severity_level::Fatal);
		throw;
	}


	void session::shedule_handle_of_request() noexcept try
	{
		parser_.emplace(std::piecewise_construct, std::make_tuple(), std::make_tuple());

		beast_http::async_read(socket_, read_stream_buffer_, *parser_,
			[this](boost::system::error_code _error, [[maybe_unused]] size_t _bytes_transferred) -> void
			{
				if (_error)
				{
					logger_.log("Error recive request: " + _error.message(), file_logger::severity_level::Error);
				}

				std::cout << "Target: " << parser_->get().target() << std::endl; // helper information

				if (socket_.is_open())
				{
					shedule_response(parser_->get());
				}
			});
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Request error: " + std::string(_ex.what()), file_logger::severity_level::Error);
	}



	void session::shedule_response(const request_t& _request) noexcept try
	{
		response_ = request_handler(_request);

		response_serializer_.emplace(std::move(*response_));

		beast_http::async_write(socket_, *response_serializer_,
			[this](boost::system::error_code _error, [[maybe_unused]] size_t _bytes_transfered) -> void
			{
				if (_error)
				{
					logger_.log("Error send response: " + _error.message(), file_logger::severity_level::Error);
				}
			});
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Response error: " + std::string(_ex.what()), file_logger::severity_level::Error);
	}
}