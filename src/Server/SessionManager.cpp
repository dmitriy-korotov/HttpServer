#include "SessionManager.hpp"

#include "Session.hpp"

#include <iostream>



static constexpr std::string_view DEFAULT_FILE_LOGGER_NAME = "SessionManagerLog";



namespace http
{
	SessionManager::SessionManager(const std::string& _path_to_log_directory)
			: m_logger(DEFAULT_FILE_LOGGER_NAME.data(), _path_to_log_directory)
	{ }



	void SessionManager::startNewSession(session_ptr _session_ptr) noexcept
	{
		auto added_session = m_opened_sessions.emplace(std::move(_session_ptr));
		if (added_session.second)
		{
			(*added_session.first)->start();
			m_logger.log("Started new session: " + (*added_session.first)->info(), FileLogger::SeverityLevel::Info);
		}
		else
		{
			m_logger.log("Can't start new session", FileLogger::SeverityLevel::Error);
		}
	}



	void SessionManager::closeSession(session_ptr _session_ptr) noexcept
	{
		m_opened_sessions.erase(_session_ptr);
		_session_ptr->close();
		m_logger.log("Closed session: " + _session_ptr->info(), FileLogger::SeverityLevel::Info);
	}



	void SessionManager::closeAllSessions() noexcept
	{
		std::for_each(m_opened_sessions.begin(), m_opened_sessions.end(),
			[logger = &m_logger](session_ptr _sesion) -> void
			{
				_sesion->close();
				logger->log("Closed session: " + _sesion->info(), FileLogger::SeverityLevel::Info);
			});
		m_opened_sessions.clear();
	}
}