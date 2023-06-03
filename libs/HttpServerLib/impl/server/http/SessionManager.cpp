#include <http/SessionManager.hpp>

#include <http/Session.hpp>

#include <iostream>



static constexpr std::string_view DEFAULT_FILE_LOGGER_NAME = "SessionManagerLog";



namespace http
{
	session_manager::session_manager(http_server& _server, const path& _path_to_log_directory)
			: server_(_server)
			, logger_(DEFAULT_FILE_LOGGER_NAME.data(), _path_to_log_directory)
	{ }



	void session_manager::startNewSession(socket_t&& _session_socket)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		auto added_session = sessions_.insert(std::make_shared<session>(std::move(_session_socket), server_, *this, logger_));
		if (!added_session.second)
		{
			logger_.log("Can't start new session: " + (*added_session.first)->info(), file_logger::severity_level::Error);
			return;
		}
		(*added_session.first)->start();
		std::cout << "This thread: " << std::this_thread::get_id() << "\nSessions: " << sessions_.size() << std::endl;	// helper information
	}



	void session_manager::closeSession(session_ptr&& _session_ptr) noexcept
	{
		std::lock_guard<std::mutex> lock(mutex_);
		sessions_.erase(_session_ptr);
		_session_ptr->close();
		std::cout << "This thread: " << std::this_thread::get_id() << "\nSessions: " << sessions_.size() << std::endl;	// helper information
	}



	void session_manager::closeAllSessions() noexcept
	{
		std::lock_guard<std::mutex> lock(mutex_);
		std::for_each(sessions_.begin(), sessions_.end(),
			[this, logger = &logger_](const session_ptr& _session) -> void
			{
				_session->close();
			});
		sessions_.clear();
	}
}