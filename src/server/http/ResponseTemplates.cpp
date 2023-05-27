#include "http/ResponseTemplates.hpp"



namespace http::response::templates
{
	response_t getBadResponse(const beast_http::status _status, const std::string& _server_name)
	{
		response_t _response;
		_response.result(_status);
		_response.keep_alive(false);
		_response.set(beast_http::field::server, _server_name);
		_response.set(beast_http::field::content_type, "text/html");
		_response.prepare_payload();
		return _response;
	}
}