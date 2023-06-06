#pragma once

#include <iostream>



namespace http::request
{
	enum class EContentType : uint8_t
	{
		multipart_form_data,
		application_form_url_encoded,
		text_html,
		text_css,
		text_js,
		text_plain,
		image_png,
		image_jpg,
		image_jpeg,
		image_ico,
		application_pdf
	};



	std::string convertExtentionToContentType(const std::string_view& _extention);
	EContentType toContentTypeEnum(const std::string_view& _string_content_type);
}