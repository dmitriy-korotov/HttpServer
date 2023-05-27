#pragma once
#ifndef SESSION_HPP
#define SESSION_HPP

#include "Defines.hpp"

#include "FileLogger.hpp"
#include "HttpServer.hpp"
#include "ResponseTypes.hpp"

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/beast/http/serializer.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>

#include <memory>



namespace http
{
	class session_manager;



	namespace beast_http = boost::beast::http;
	using namespace response;
	using boost::filesystem::path;
	
	

	class session : public std::enable_shared_from_this<session>, boost::noncopyable
	{
	public:

		using socket_t =				boost::asio::ip::tcp::socket;
		using buffer_t =				boost::beast::flat_static_buffer<8192>;
		using request_parser_t =		beast_http::request_parser<body_t, alloc_t>;
		using response_serializer_t =	beast_http::response_serializer<body_t, fields_t>;



		session(session&&) = default;
		session& operator=(session&&) = default;

		session(socket_t&& _socket, http_server& _server, session_manager& _session_manager, file_logger& _logger);

		void start() noexcept;
		void close() noexcept;

		std::string info() const noexcept;

	private:

		void check_deadline();
		void shedule_handle_of_request() noexcept;
		void shedule_response(const request_t& _request) noexcept;

		response_t request_handler(const request_t& _request) const;

	private:

		socket_t socket_;

		http_server& server_;
		session_manager& session_manager_;

		boost::asio::steady_timer request_deadline_ = { server_.acceptor_.get_executor(), (std::chrono::steady_clock::time_point::max)() };

		buffer_t read_stream_buffer_;

		std::optional<response_t> response_;
		std::optional<request_parser_t> parser_;
		std::optional<response_serializer_t> response_serializer_;

		file_logger& logger_;

	};
}

#endif // SESSION_HPP
