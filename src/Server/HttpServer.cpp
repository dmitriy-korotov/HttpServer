#include "HttpServer.hpp"

#include "Session.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <sstream>



static constexpr std::string_view DEFAULT_FILE_LOGGER_NAME = "ServerLog";



namespace http
{
	HttpServer::HttpServer(boost::asio::io_context& _io_context, std::uint16_t _port, const std::string& _path_to_documents_root,
						   size_t _amount_trheads, const std::string& _path_to_log_root) noexcept
			: m_io_context(_io_context)
			, m_thread_pool(_amount_trheads)
			, m_socket(m_io_context)
			, m_acceptor(m_io_context, endpoint_t(ip::tcp::v4(), _port))
			, m_path_to_documents_root(_path_to_documents_root)
			, m_logger(DEFAULT_FILE_LOGGER_NAME.data(), _path_to_log_root)
			, m_session_manager(_path_to_log_root)
	{ }



	void HttpServer::start() noexcept
	{
		async_accept_handler();
	}



	void HttpServer::shutdown() noexcept
	{
		m_acceptor.close();
		m_socket->close();
	}



	void HttpServer::async_accept_handler() noexcept
	{
		m_socket.emplace(m_io_context);

		m_acceptor.async_accept(*m_socket, 
			[this](boost::system::error_code _error) -> void
			{
				if (!_error)
				{
					m_logger.log(std::move("Request from: " + m_socket->remote_endpoint().address().to_string()), FileLogger::SeverityLevel::Info);
					m_session_manager.startNewSession(boost::make_shared<Session>(std::move(*m_socket), m_path_to_documents_root));
					async_accept_handler();
				}
				else
				{
					m_logger.log(_error.message(), FileLogger::SeverityLevel::Fatal);
				}
			});
	}
}