#pragma once
#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include "Defines.hpp"

#include "FileLogger.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/unordered_set.hpp>



namespace http
{
	class Session;

	class SessionManager
	{
	public:

		using session_ptr = boost::shared_ptr<Session>;

		SessionManager(const SessionManager&) = delete;
		SessionManager& operator=(const SessionManager&) = delete;

		SessionManager(const std::string& _path_to_log_directory);
		SessionManager(SessionManager&&) = default;
		SessionManager& operator=(SessionManager&&) = default;

		void startNewSession(session_ptr _session_ptr) noexcept;
		void closeSession(session_ptr _session_ptr) noexcept;

		void closeAllSessions() noexcept;

	private:

		FileLogger m_logger;

		boost::unordered_set<session_ptr> m_opened_sessions;

	};
}

#endif // !SESSION_MANAGER_HPP
