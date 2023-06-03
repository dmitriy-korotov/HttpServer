#include <http/ResponseGenerators.hpp>

#include <http/Response.hpp>

#include <system/FileReader.hpp>

#include <unordered_map>



static const std::unordered_map<http::response::EResponseContentType, boost::beast::string_view> resonse_content_types_ = 
{
	{ http::response::EResponseContentType::Plain,		"text/plain"},
	{ http::response::EResponseContentType::HTML,		"text/html"},
	{ http::response::EResponseContentType::JSON,		"text/json"},
	{ http::response::EResponseContentType::XML,		"text/xml"}
};



namespace http::response
{
	static response_t __commonSendResponse(std::string&& _string_response, EResponseContentType _response_fromat)
	{
		response_t _response;
		_response.set(beast_http::field::content_type, resonse_content_types_.at(_response_fromat));
		_response.body() = std::move(_string_response);
		return _response;
	}



	response_t createResponse(std::string&& _string_response)
	{
		return __commonSendResponse(std::move(_string_response), EResponseContentType::Plain);
	}



	response_t createResponseHTML(std::string&& _string_response)
	{
		return __commonSendResponse(std::move(_string_response), EResponseContentType::HTML);
	}



	response_t renderTemplate(const boost::filesystem::path& _path)
	{
		response_t _response;
		_response.set(beast_http::field::content_type, "text/html");

		file_reader _file_reader(_path);
		_response.body() = std::move(_file_reader.data());

		return _response;
	}



	response_t createResponseJSON(std::string&& _string_response)
	{
		return __commonSendResponse(std::move(_string_response), EResponseContentType::JSON);
	}



	response_t createResponseXML(std::string&& _string_response)
	{
		return __commonSendResponse(std::move(_string_response), EResponseContentType::XML);
	}
}