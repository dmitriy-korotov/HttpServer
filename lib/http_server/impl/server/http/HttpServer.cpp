#include <webcpp/http/HttpServer.hpp>

#include <webcpp/http/Request.hpp>
#include <webcpp/http/Response.hpp>
#include <webcpp/http/ResponseGenerators.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include <iostream>



static constexpr std::string_view DEFAULT_FILE_LOGGER_NAME = "Server";




static http::response_t testGetHandler(const http::request_t& _request)
{
	auto& get = _request.GET();

	std::cout << "Query params: " << get.size() << std::endl;

	for (const auto& item : get)
	{
		std::cout << item.first << '=' << item.second<< std::endl;
	}
	return http::response::renderTemplate("C:/Users/User/MyProjects/HttpServer/res/templates/checkers.html");
}



static http::response_t testPostHandler(const http::request_t& _request)
{
	if (_request.method() == http::beast_http::verb::post)
	{
		for (const auto& item : _request)
		{
			std::cout << item.name() << " : " << item.value() << std::endl;
		}
		const auto& POST = _request.POST();
		for (const auto& item : std::get<http::request_t::key_value_t>(POST))
		{
			std::cout << item.first << " : " << item.second << std::endl;
		}
	}

	return http::response::renderTemplate("C:/Users/User/MyProjects/HttpServer/res/templates/registration.html");
}



namespace http
{
	http_server::http_server(const std::string _address, uint16_t _port, const path& _path_to_documents_root, const path& _path_to_log_root)
			: io_context_(1)
			, thread_pool_()
			, acceptor_(io_context_)
			, signals_(io_context_)
			, document_root_(_path_to_documents_root)
			, logger_(DEFAULT_FILE_LOGGER_NAME.data(), _path_to_log_root)
			, session_manager_(*this, _path_to_log_root)
	{ 
		logger_.log((boost::format("Server runing on address %1%:%2%") % _address % _port).str(), file_logger::severity_level::Info);

		setup_signals();
		setup_acceptor(_address, _port);
	}



	void http_server::run() try
	{
		registrateURLHandler("/test", testGetHandler);
		registrateURLHandler("/registration", testPostHandler);

		for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
		{
			post(thread_pool_, [this]() { io_context_.run(); });
		}
		thread_pool_.join();
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Can't run server: " + std::string(_ex.what()), file_logger::severity_level::Fatal);
		throw;
	}



	void http_server::setup_signals() try
	{
		signals_.add(SIGINT);
		signals_.add(SIGTERM);
#ifdef SIGQUIT
		signals_.add(SIGQUIT);
#endif // SIGQUIT

		shedule_await_stop();
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Can't setup signals: " + std::string(_ex.what()), file_logger::severity_level::Fatal);
		throw;
	}



	void http_server::setup_acceptor(const std::string& _address, uint16_t _port) try
	{
		ip::tcp::resolver _resolver(io_context_);
		endpoint_t _endpoint = *_resolver.resolve(_address, boost::lexical_cast<std::string>(_port)).begin();
		acceptor_.open(_endpoint.protocol());
		acceptor_.set_option(socket_base::reuse_address(true));
		acceptor_.bind(_endpoint);
		acceptor_.listen();
		
		shedule_accept();
	}
	catch (const std::exception& _ex)
	{
		logger_.log("Setup acceptor error: " + std::string(_ex.what()), file_logger::severity_level::Fatal);
		throw;
	}



	void http_server::shedule_await_stop() noexcept
	{
		signals_.async_wait(
			[this](boost::system::error_code _error, [[maybe_unused]] int _signo) -> void
			{
				if (_error)
				{
					logger_.log("Signals stop error: " + _error.message(), file_logger::severity_level::Error);
				}
				logger_.log("Server finished.", file_logger::severity_level::Info);
				acceptor_.close();
				session_manager_.closeAllSessions();
			});
	}



	void http_server::shedule_accept() noexcept
	{
		acceptor_.async_accept( 
			[this](boost::system::error_code _error, socket_t _socket) -> void
			{
				if (!acceptor_.is_open())
				{
					return;
				}

				if (!_error)
				{
					session_manager_.startNewSession(std::move(_socket));
				}
				else
				{
					logger_.log("Accept error: " + _error.message(), file_logger::severity_level::Error);
				}

				shedule_accept();
			});
	}



	void http_server::setPathToDocumentRoot(const path& _path_to_doc_root) noexcept
	{
		document_root_ = _path_to_doc_root;
	}



	const path& http_server::getPathToDocumentRoot() const noexcept
	{
		return document_root_;
	}




	bool http_server::registrateURLHandler(const std::string_view _URL, URLhandler&& _URL_handler)
	{
		auto it = URL_handlres_map_.emplace(_URL, std::move(_URL_handler));
		if (!it.second)
		{
			logger_.log("Can't registrate handler for this URL: " + std::string(_URL), file_logger::severity_level::Error);
			return false;
		}
		return true;
	}
}