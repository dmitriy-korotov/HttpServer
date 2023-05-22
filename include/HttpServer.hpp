#pragma once
#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include "Defines.hpp"

#include "SessionManager.hpp"
#include "FileLogger.hpp"

#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/optional.hpp>

#include <iostream>



static constexpr std::string_view DEFAULT_LOG_ROOT = "../log";



namespace http
{
	using namespace boost::asio;


	
	class HttpServer
	{
	public:

		using acceptor_t = ip::tcp::acceptor;
		using socket_t = ip::tcp::socket;
		using endpoint_t = ip::tcp::endpoint;



		HttpServer(const HttpServer&) = delete;
		HttpServer& operator=(const HttpServer&) = delete;



		HttpServer(HttpServer&&) = default;
		HttpServer& operator=(HttpServer&&) = default;
		~HttpServer() = default;



		HttpServer(io_context& _io_context, std::uint16_t _port, const std::string& _path_to_documents_root,
				   size_t _amount_trheads = 1, const std::string& _path_to_log_root = DEFAULT_LOG_ROOT.data()) noexcept;

		void start() noexcept;
		void shutdown() noexcept;

	protected:

		void async_accept_handler() noexcept;

	protected:

		io_context& m_io_context;
		thread_pool m_thread_pool;
		
		boost::optional<socket_t> m_socket;
		acceptor_t m_acceptor;

		std::string m_path_to_documents_root;
		FileLogger m_logger;

		SessionManager m_session_manager;
	};
}

#endif // !HTTP_SERVER_HPP
