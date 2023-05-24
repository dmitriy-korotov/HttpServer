#include "SessionManager.hpp"

#include "Session.hpp"

#include <iostream>



static constexpr std::string_view DEFAULT_FILE_LOGGER_NAME = "SessionManagerLog";



namespace http
{
	session_manager::session_manager(const path& _path_to_log_directory)
			: logger_(DEFAULT_FILE_LOGGER_NAME.data(), _path_to_log_directory)
	{ }



	void session_manager::startNewSession(socket_t&& _session_socket)
	{
		auto added_session = sessions_.insert(std::make_shared<session>(std::move(_session_socket), logger_));
		if (!added_session.second)
		{
			logger_.log("Can't start new session: " + (*added_session.first)->info(), file_logger::SeverityLevel::Error);
			return;
		}
		(*added_session.first)->start();
	}



	void session_manager::closeSession(session_ptr&& _session_ptr) noexcept
	{
		sessions_.erase(_session_ptr);
		_session_ptr->close();
	}



	void session_manager::closeAllSessions() noexcept
	{
		std::for_each(sessions_.begin(), sessions_.end(),
			[this, logger = &logger_](const session_ptr& _session) -> void
			{
				_session->close();
			});
		sessions_.clear();
	}
}