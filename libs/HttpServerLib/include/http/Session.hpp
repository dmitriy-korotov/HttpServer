#pragma once

#include <http/Defines.hpp>
#include <http/HttpTypes.hpp>

#include <http/SessionManager_fwd.hpp>
#include <http/HttpServer_fwd.hpp>
#include <system/FileLogger_fwd.hpp>

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/beast/http/serializer.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/filesystem/path.hpp>

#include <memory>



namespace http
{
	namespace beast_http = boost::beast::http;
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
		void shedule_response(const boost_request_t& _request) noexcept;

		boost_response_t request_handler(const boost_request_t& _request) const noexcept;

	private:

		socket_t socket_;

		http_server& server_;
		session_manager& session_manager_;

		boost::asio::steady_timer request_deadline_;

		buffer_t read_stream_buffer_;

		std::optional<boost_response_t> response_;
		std::optional<request_parser_t> parser_;
		std::optional<response_serializer_t> response_serializer_;

		file_logger& logger_;

	};
}