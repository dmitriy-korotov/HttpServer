#include <http/Session.hpp>

#include <system/FileLogger.hpp>
#include <system/FileReader.hpp>
#include <system/Time.hpp>

#include <http/Request.hpp>
#include <http/Response.hpp>
#include <http/SessionManager.hpp>
#include <http/HttpServer.hpp>
#include <http/ResponseTemplates.hpp>
#include <http/Url.hpp>
#include <http/ContentTypeConvertings.hpp>

#include <boost/beast/http/read.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/status.hpp>

#include <boost/filesystem.hpp>

#include <iostream>
#include <sstream>



static constexpr uint8_t REQUEST_DEADLINE_TIME = 5;
static constexpr std::string_view SERVER_NAME = "Dmitriy.Korotov";



namespace http
{
	session::session(socket_t&& _socket, http_server& _server, session_manager& _session_manager, file_logger& _logger)
			: socket_(std::move(_socket))
			, server_(_server)
			, request_deadline_ { server_.acceptor_.get_executor(), (std::chrono::steady_clock::time_point::max)() }
			, session_manager_(_session_manager)
			, logger_(_logger)
	{ }



	void session::start() noexcept
	{
		//check_deadline();
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
			logger_.log("Closing session error: " + _error.message(), file_logger::severity_level::Error);
		}
	}



	void session::check_deadline() try
	{
		if (request_deadline_.expiry() <= std::chrono::steady_clock::now())
		{
			session_manager_.closeSession(shared_from_this());
			return;
		}
		request_deadline_.expires_from_now(std::chrono::seconds(REQUEST_DEADLINE_TIME));

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
		read_stream_buffer_.consume(read_stream_buffer_.size());

		beast_http::async_read(socket_, read_stream_buffer_, *parser_,
			[this, self = shared_from_this()](boost::system::error_code _error, [[maybe_unused]] size_t _bytes_transferred) -> void
			{
				if (_error)
				{
					logger_.log("Error recive request: " + _error.message(), file_logger::severity_level::Error);
					return;
				}
				shedule_response(parser_->get());
			});
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Request error: " + std::string(_ex.what()), file_logger::severity_level::Error);
	}



	void session::shedule_response(const boost_request_t& _request) noexcept try
	{
		response_ = request_handler(_request);

		response_serializer_.emplace(std::move(*response_));

		beast_http::async_write(socket_, *response_serializer_,
			[this, self = shared_from_this()](boost::system::error_code _error, [[maybe_unused]] size_t _bytes_transfered) mutable -> void
			{
				if (_error)
				{
					logger_.log("Error send response: " + _error.message(), file_logger::severity_level::Error);
					return;
				}
				//shedule_handle_of_request();
				session_manager_.closeSession(std::move(self));
			});
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Response error: " + std::string(_ex.what()), file_logger::severity_level::Error);
	}



	boost_response_t session::request_handler(const boost_request_t& _request) const noexcept try
	{
		boost_response_t response_;
		std::string _target = _request.target();
		
		if (_request.method() == beast_http::verb::get && request::url::isPathToSourceFile(_target))
		{
			auto path_to_file = server_.document_root_ / _target;
			if (!boost::filesystem::exists(path_to_file))
			{
				logger_.log("File don't exists: " + path_to_file.string(), file_logger::severity_level::Warning);
				return response::templates::getBadResponse(beast_http::status::not_found, SERVER_NAME.data());
			}

			response_.set(beast_http::field::content_type,
							request::convertExtentionToContentType(boost::filesystem::extension(_target)));

			file_reader file_reader_(path_to_file);
			response_.body() = std::move(file_reader_.data());
		}
		else
		{
			auto path_without_query_string = request::url::parseRelativePath(_target);
			auto handler_it = server_.URL_handlres_map_.find(path_without_query_string);
			if (handler_it == server_.URL_handlres_map_.end())
			{
				return response::templates::getBadResponse(beast_http::status::not_found, SERVER_NAME.data());
			}
			response_ = handler_it->second(_request);
		}
		
		response_.result(beast_http::status::ok);
		response_.keep_alive(false);
		response_.set(beast_http::field::server, SERVER_NAME.data());
		response_.prepare_payload();

		return response_;
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Request handler error: " + std::string(_ex.what()), file_logger::severity_level::Error);
		return response::templates::getBadResponse(beast_http::status::bad_request, SERVER_NAME.data());
	}
}