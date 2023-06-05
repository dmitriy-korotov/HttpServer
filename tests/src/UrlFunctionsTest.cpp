#include <boost/test/unit_test.hpp>

#include <http/Url.hpp>



BOOST_AUTO_TEST_SUITE(TestUrlFunctions)

BOOST_AUTO_TEST_CASE(IsPathToSourceFile)
{
	bool is_path_to_source = http::request::url::isPathToSourceFile("http://localhost.com/home/index.html");
	BOOST_TEST(is_path_to_source == true);
}

BOOST_AUTO_TEST_CASE(IsNotPathToSourceFile)
{
	bool is_path_to_source = http::request::url::isPathToSourceFile("http://localhost.com/home/user");
	BOOST_TEST(is_path_to_source == false);
}

BOOST_AUTO_TEST_CASE(EmptyPath)
{
	bool is_path_to_source = http::request::url::isPathToSourceFile("");
	BOOST_TEST(is_path_to_source == false);
}

BOOST_AUTO_TEST_CASE(TwoLuevelsDeepth)
{
	auto parsed_path = http::request::url::parseRelativePath("http://google.com/home/user");
	BOOST_TEST(parsed_path == "/home/user");
}

BOOST_AUTO_TEST_CASE(TwoLuevelsDeepthWidthQueryString)
{
	auto parsed_path = http::request::url::parseRelativePath("http://google.com/home/user?name=surname&Dima=Korotov");
	BOOST_TEST(parsed_path == "/home/user");
}

BOOST_AUTO_TEST_CASE(ZeroLuevelsDeepth)
{
	auto parsed_path = http::request::url::parseRelativePath("http://google.com/");
	BOOST_TEST(parsed_path == "/");
}

BOOST_AUTO_TEST_CASE(ZeroLuevelsDeepthWidthQueryString)
{
	auto parsed_path = http::request::url::parseRelativePath("http://google.com/?name=surname&Dima=Korotov");
	BOOST_TEST(parsed_path == "/");
}

BOOST_AUTO_TEST_CASE(ConvertionEtentions)
{
	auto png = http::request::url::convertExtentionToContentType(".png");
	auto jpg = http::request::url::convertExtentionToContentType(".jpg");
	auto jpeg = http::request::url::convertExtentionToContentType(".jpeg");
	auto ico = http::request::url::convertExtentionToContentType(".ico");
	auto pdf = http::request::url::convertExtentionToContentType(".pdf");
	auto html = http::request::url::convertExtentionToContentType(".html");
	auto css = http::request::url::convertExtentionToContentType(".css");
	auto js = http::request::url::convertExtentionToContentType(".js");

	BOOST_TEST(png == "image/png");
	BOOST_TEST(jpg == "image/jpg");
	BOOST_TEST(jpeg == "image/jpeg");
	BOOST_TEST(ico == "image/ico");
	BOOST_TEST(pdf == "application/pdf");
	BOOST_TEST(html == "text/html");
	BOOST_TEST(css == "text/css");
	BOOST_TEST(js == "text/javascript");
}

BOOST_AUTO_TEST_SUITE_END()