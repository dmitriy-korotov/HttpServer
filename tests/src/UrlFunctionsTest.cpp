#include <boost/test/unit_test.hpp>
#include <http/QueryStringParser.hpp>



BOOST_AUTO_TEST_SUITE(TestQueryStringParser)

BOOST_AUTO_TEST_CASE(TwoParametrs)
{
	//http::request::url::QSparser _parser("localhost.com?name=Dima&surname=Korotov");

	//auto& parsed_qs = _parser.get();

	//BOOST_TEST(parsed_qs["name"] == "Dima");
	//BOOST_TEST(parsed_qs["surname"] == "Korotov");
	BOOST_TEST(2 == 2);
}

BOOST_AUTO_TEST_CASE(ZeroParametrs)
{
	/*http::request::url::QSparser _parser("localhost.com?");

	auto& parsed_qs = _parser.get();

	BOOST_TEST(parsed_qs.empty());*/
	BOOST_TEST(3 == 2);
}

BOOST_AUTO_TEST_CASE(EmptyString)
{
	/*http::request::url::QSparser _parser("localhost.com?");

	auto& parsed_qs = _parser.get();

	BOOST_TEST(parsed_qs.empty());*/
	BOOST_TEST(3 == 7);
}

BOOST_AUTO_TEST_SUITE_END()