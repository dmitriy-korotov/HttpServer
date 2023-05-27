#include "Session.hpp"

#include "FileReader.hpp"
#include "SessionManager.hpp"
#include "HttpServer.hpp"

#include <boost/beast/http/read.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/status.hpp>

#include <iostream>
#include <sstream>



constexpr uint8_t REQUEST_DEADLINE_TIME = 10;
constexpr std::string_view SERVER_NAME = "Dmitriy.Korotov";



namespace http
{
	static response_t __get_bad_response(const beast_http::status _status)
	{
		response_t _response;
		_response.result(_status);
		_response.keep_alive(false);
		_response.set(beast_http::field::server, SERVER_NAME);
		_response.prepare_payload();
		return _response;
	}





	response_t session::request_handler(const request_t& _request) const
	{
		response_t response_;
		response_.keep_alive(false);

		std::string request_target_(_request.target().begin(), _request.target().size());
		size_t point_position = request_target_.find_last_of('.');
		std::string extention = point_position < request_target_.length() ? request_target_.substr(point_position + 1, request_target_.length() - point_position) : "";

		if (request_target_ == "/")
		{
			response_.set(beast_http::field::content_type, "text/html");
			file_reader file_reader_(server_.document_root_ / "templates" / "checkers.html");
			
			response_.body() = std::move(file_reader_.data());
		}
		else if (extention == "css")
		{
			response_.set(beast_http::field::content_type, "text/css");
			file_reader file_reader_(server_.document_root_ / std::string(request_target_));

			response_.body() = std::move(file_reader_.data());
		}
		else if (extention == "js")
		{
			response_.set(beast_http::field::content_type, "text/javascript");
			file_reader file_reader_(server_.document_root_ / std::string(request_target_));

			response_.body() = std::move(file_reader_.data());
		}
		else if (extention == "png" || extention == "jpg" || extention == "jpeg" || extention == "ico")
		{
			response_.set(beast_http::field::content_type, "image/" + extention);
			file_reader file_reader_(server_.document_root_ / std::string(request_target_));

			response_.body() = std::move(file_reader_.data());
		}
		else
		{
			return __get_bad_response(beast_http::status::not_found);
		}

		response_.result(beast_http::status::ok);
		response_.prepare_payload();

		return response_;
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