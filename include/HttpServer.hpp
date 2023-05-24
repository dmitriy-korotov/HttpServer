#pragma once
#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include "Defines.hpp"

#include "SessionManager.hpp"
#include "FileLogger.hpp"

#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/noncopyable.hpp>

#include <iostream>



namespace http
{
	using namespace boost::asio;
	using namespace boost::filesystem;


	
	class http_server : boost::noncopyable
	{
	public:

		using acceptor_t = ip::tcp::acceptor;
		using socket_t = ip::tcp::socket;
		using endpoint_t = ip::tcp::endpoint;


		
		http_server(http_server&&) = default;
		http_server& operator=(http_server&&) = default;
		~http_server() = default;



		http_server(const std::string _address, uint16_t _port,
					const path& _path_to_documents_root,	const path& _path_to_log_root);

		void run();

	protected:

		void setup_signals();
		void setup_acceptor(const std::string& _address, uint16_t _port);
		void shedule_accept();

		void shedule_await_stop() noexcept;

	protected:

		io_context io_context_;
		thread_pool thread_pool_;
		
		acceptor_t acceptor_;
		signal_set signals_;
		
		path document_root_;
		
		session_manager session_manager_;
		
		file_logger logger_;

	};
}

#endif // !HTTP_SERVER_HPP
