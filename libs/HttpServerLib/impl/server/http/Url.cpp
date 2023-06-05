#include <http/Url.hpp>
#include <http/Defines.hpp>

#include <unordered_map>



namespace http::request::url
{
	static const std::unordered_map<std::string_view, std::string_view> extention_to_content_type_map_ =
	{
		{ ".html",	"text/html" },
		{ ".js",	"text/javascript" },
		{ ".css",	"text/css" },
		{ ".png",	"image/png" },
		{ ".jpeg",	"image/jpeg" },
		{ ".jpg",	"image/jpg" },
		{ ".ico",	"image/ico" },
		{ ".pdf",	"application/pdf" }
	};
	




	bool isPathToSourceFile(const std::string_view& _target)
	{
		size_t extention_position = _target.find_last_of('.');
		return (extention_position != std::string::npos && _target.find_first_of('/', extention_position) == std::string::npos);
	}



	std::string convertExtentionToContentType(const std::string_view& _extention)
	{
		return std::string(extention_to_content_type_map_.at(_extention));
	}



	std::string parseRelativePath(const std::string_view& _target)
	{
		size_t question_position = _target.find_first_of('?');
		size_t start_server_domen = _target.find_first_of("//");
		size_t start_relative_path = (start_server_domen == std::string::npos) ? 0 : _target.find_first_of('/', start_server_domen + 2);

		return (question_position != std::string::npos) ?
								std::string(_target.substr(start_relative_path, question_position - start_relative_path)) 
								:
								std::string(_target.substr(start_relative_path, _target.length() - start_relative_path));
	}
}