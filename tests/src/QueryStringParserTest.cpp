#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE HTTP_TESTS
#include <boost/test/unit_test.hpp>

#include <http/QueryStringParser.hpp>



BOOST_AUTO_TEST_SUITE(TestQueryStringParser)

BOOST_AUTO_TEST_CASE(TWO_PARAMETRS)
{
	http::request::url::QSparser _parser("localhost.com?name=Dima&surname=Korotov");

	auto& parsed_qs = _parser.get();

	BOOST_TEST(parsed_qs["name"] == "Dima");
	BOOST_TEST(parsed_qs["surname"] == "Korotov");
}

BOOST_AUTO_TEST_CASE(ZERO_PARAMETRS)
{
	http::request::url::QSparser _parser("localhost.com?");

	auto& parsed_qs = _parser.get();

	BOOST_TEST(parsed_qs.empty());
}

BOOST_AUTO_TEST_SUITE_END()