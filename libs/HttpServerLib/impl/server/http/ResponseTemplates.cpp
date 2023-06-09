#include <http/ResponseTemplates.hpp>

#include <boost/beast/http/status.hpp>

#include <unordered_map>



namespace http::response::templates
{
	constexpr std::string_view styles_ = 
		"* {\nmargin: 0px;\npadding: 0px\n}\n"
		"body {\ndisplay: grid;\nalign-items: center;\nalign-content: center;\nheight: 100%;\nwidth: 100%;\n"
		"background-image: url('images/ErrorBg.jpeg');\nbackground-size: cover;\n}\n"
		"#message {\nfont-size: 5em;\ntext-align: center; background-color: #b3a6c2; padding: 15px; border: 3px solid black;\n}\n";

	static const std::unordered_map<beast_http::status, std::string_view> status_to_string_map_ =
	{
		{ beast_http::status::not_found,					"Not found 404" },
		{ beast_http::status::bad_gateway,					"Bad gateway 502" },
		{ beast_http::status::bad_request,					"Bad request 400" },
		{ beast_http::status::too_many_requests,			"Too many requests 429" },
		{ beast_http::status::client_closed_request,		"Client closed request 499" },
		{ beast_http::status::service_unavailable,			"Service unavailable 503" }
	};





	std::string to_string(beast_http::status _status)
	{
		return status_to_string_map_.at(_status).data();
	}



	std::string getBodyHTML(beast_http::status _status) noexcept
	{
		std::ostringstream body;
		body << "<html><head><style>" << styles_
			 << "</style></head><body><div id='message'><h>"
			 << to_string(_status)
			 << "</h></div></body></html>";
		return body.str();
	}



	boost_response_t getBadResponse(const beast_http::status _status, const std::string& _server_name)
	{
		boost_response_t _response;
		_response.result(_status);
		_response.keep_alive(false);
		_response.set(beast_http::field::server, _server_name);
		_response.set(beast_http::field::content_type, "text/html");
		_response.body() = getBodyHTML(_status);
		_response.prepare_payload();
		return _response;
	}
}