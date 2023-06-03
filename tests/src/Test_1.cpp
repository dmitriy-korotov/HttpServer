#include <http/QueryStringParser.hpp>

#define BOOST_TEST_MODULE QUERY_STRING_PARSER
#include <boost/test/unit_test.hpp>




BOOST_AUTO_TEST_CASE(QUERY_STRING_PARSER_TEST)
{
	http::request::url::QSparser _parser1("localhost.com?name=Dima&surname=Korotov");

	auto parsed_qs1 = _parser1.get();

	BOOST_TEST(parsed_qs1["name"] == "Dima");
	BOOST_TEST(parsed_qs1["surname"] == "Korotov");



	http::request::url::QSparser _parser2("localhost.com?");

	auto parsed_qs2 = _parser2.get();

	BOOST_TEST(parsed_qs2.empty());



	http::request::url::QSparser _parser3("localhost.com");

	auto parsed_qs3 = _parser3.get();

	BOOST_TEST(parsed_qs3.empty());
}