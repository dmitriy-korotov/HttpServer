#include "ResponseGenerators.hpp"

#include "FileReader.hpp"

#include <unordered_map>



static const std::unordered_map<http::response::EResponseFormat, boost::beast::string_view> resonse_formates_ = 
{
	{ http::response::EResponseFormat::Plain, "text/plain"},
	{ http::response::EResponseFormat::HTML, "text/html"},
	{ http::response::EResponseFormat::JSON, "text/json"},
	{ http::response::EResponseFormat::XML, "text/xml"}
};



namespace http::response
{
	static response_t __commonSendResponse(std::string&& _string_response, EResponseFormat _response_fromat)
	{
		response_t _response;
		_response.result(beast_http::status::ok);
		_response.set(beast_http::field::content_type, resonse_formates_.at(_response_fromat));
		_response.body() = std::move(_string_response);
		_response.prepare_payload();
		return _response;
	}



	response_t sendResponse(std::string&& _string_response)
	{
		return __commonSendResponse(std::move(_string_response), EResponseFormat::Plain);
	}



	response_t sendResponseHTML(std::string&& _string_response)
	{
		return __commonSendResponse(std::move(_string_response), EResponseFormat::HTML);
	}



	response_t templateRender(const boost::filesystem::path& _path)
	{
		response_t _response;
		_response.result(beast_http::status::ok);
		_response.set(beast_http::field::content_type, "text/html");

		file_reader _file_reader(_path);
		_response.body() = std::move(_file_reader.data());

		_response.prepare_payload();
		return _response;
	}



	response_t sendResponseJSON(std::string&& _string_response)
	{
		return __commonSendResponse(std::move(_string_response), EResponseFormat::JSON);
	}



	response_t sendResponseXML(std::string&& _string_response)
	{
		return __commonSendResponse(std::move(_string_response), EResponseFormat::XML);
	}
}