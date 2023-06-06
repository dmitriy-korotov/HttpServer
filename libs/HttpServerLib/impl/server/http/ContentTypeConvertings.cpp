#include <http/ContentTypeConvertings.hpp>

#include <unordered_map>



namespace http::request
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



	static const std::unordered_map<std::string_view, EContentType> string_content_type_convert_to_enum_ =
	{
		{ "text/html",										EContentType::text_html },
		{ "text/javascript",								EContentType::text_js },
		{ "text/css",										EContentType::text_css },
		{ "image/png",										EContentType::image_png },
		{ "image/jpeg",										EContentType::image_jpeg },
		{ "image/jpg",										EContentType::image_jpg },
		{ "image/ico",										EContentType::image_ico },
		{ "application/pdf",								EContentType::application_pdf },
		{ "application/x-www-form-urlencoded",				EContentType::application_form_url_encoded },
		{ "multipart/form-data",							EContentType::multipart_form_data }
	};



	std::string convertExtentionToContentType(const std::string_view& _extention)
	{
		return std::string(extention_to_content_type_map_.at(_extention));
	}



	EContentType toContentTypeEnum(const std::string_view& _string_content_type)
	{
		return string_content_type_convert_to_enum_.at(_string_content_type);
	}
}