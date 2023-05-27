#pragma once
#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include "Defines.hpp"
#include "HttpTypes.hpp"
#include "SessionManager.hpp"

#include "../system/FileLogger.hpp"

#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/noncopyable.hpp>

#include <string>
#include <functional>
#include <unordered_map>



namespace http
{
	class session;



	using namespace boost::asio;
	using namespace boost::filesystem;


	
	class http_server : boost::noncopyable
	{
	public:

		friend session;

		using acceptor_t = ip::tcp::acceptor;
		using socket_t = ip::tcp::socket;
		using endpoint_t = ip::tcp::endpoint;

		using URLhandler = std::function<response_t(request_t)>;

		
		http_server(http_server&&) = default;
		http_server& operator=(http_server&&) = default;
		~http_server() = default;



		http_server(const std::string _address, uint16_t _port,
					const path& _path_to_documents_root,	const path& _path_to_log_root);

		void run();

		void setPathToDocumentRoot(const path& _path_to_doc_root) noexcept;
		bool registrateURLHandler(const std::string_view _URL, URLhandler&& _URL_handler);

	private:

		void setup_signals();
		void setup_acceptor(const std::string& _address, uint16_t _port);
		
		void shedule_accept() noexcept;
		void shedule_await_stop() noexcept;

	private:

		io_context io_context_;
		thread_pool thread_pool_;

		acceptor_t acceptor_;
		signal_set signals_;
		
		path document_root_;
		
		session_manager session_manager_;
		std::unordered_map<std::string, URLhandler> URL_handlres_map_;
		
		file_logger logger_;

	};
}

#endif // !HTTP_SERVER_HPP
