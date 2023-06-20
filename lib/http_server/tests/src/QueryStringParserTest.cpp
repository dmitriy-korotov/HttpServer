#include <webcpp/http/QueryStringParser.hpp>

#include <boost/test/unit_test.hpp>



BOOST_AUTO_TEST_SUITE(QueryStringParserTest)

BOOST_AUTO_TEST_CASE(TwoKeys)
{
	http::request::url::QSparser qs_parser("/home?name=Dima&surname=Korotov");

	auto parsed_result = qs_parser.get();

	BOOST_TEST(parsed_result.at("name") == "Dima");
	BOOST_TEST(parsed_result.at("surname") == "Korotov");
}

BOOST_AUTO_TEST_CASE(ZeroKeys)
{
	http::request::url::QSparser qs_parser("http://google.com/home?");

	auto parsed_result = qs_parser.get();

	BOOST_TEST(parsed_result.empty());
}

BOOST_AUTO_TEST_CASE(OneValueEmpty)
{
	http::request::url::QSparser qs_parser("http://google.com/home?name=&surname=Korotov");

	auto parsed_result = qs_parser.get();

	BOOST_TEST(parsed_result.at("name") == "");
	BOOST_TEST(parsed_result.at("surname") == "Korotov");
}

BOOST_AUTO_TEST_CASE(KeyValueWidthSpace)
{
	http::request::url::QSparser qs_parser("http://dmitriy.korotov.miet/test?name=Dima%20Korotov");

	auto parsed_result = qs_parser.get();

	BOOST_TEST(parsed_result.at("name") == "Dima Korotov");
}

BOOST_AUTO_TEST_CASE(RU_KeyValue)
{
	http::request::url::QSparser qs_parser("http://dmitriy.korotov.miet/test?%D0%94%D0%B8%D0%BC%D0%B0=%D0%9A%D0%BE%D1%80%D0%BE%D1%82%D0%BE%D0%B2");

	auto parsed_result = qs_parser.get();

	//BOOST_TEST(parsed_result.at("Дима") == "Коротов");
}

BOOST_AUTO_TEST_SUITE_END()