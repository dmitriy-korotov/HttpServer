#pragma once
#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include <http/Defines.hpp>

#include <system/FileLogger.hpp>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include <unordered_set>



namespace http
{
	class http_server;



	using namespace boost::filesystem;


	
	class session;

	class session_manager : boost::noncopyable
	{
	public:

		using socket_t = boost::asio::ip::tcp::socket;
		using session_ptr = std::shared_ptr<session>;



		session_manager(session_manager&&) = default;
		session_manager& operator=(session_manager&&) = default;

		session_manager(http_server& _server, const path& _path_to_log_directory);

		void startNewSession(socket_t&& _session_socket);
		void closeSession(session_ptr&& _session_ptr) noexcept;

		void closeAllSessions() noexcept;

	private:

		http_server& server_;

		std::mutex mutex_; 

		std::unordered_set<session_ptr> sessions_;

		file_logger logger_;

	};
}

#endif // !SESSION_MANAGER_HPP
