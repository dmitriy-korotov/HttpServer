#include <webcpp/http/Defines.hpp>
#include <webcpp/http/Request.hpp>
#include <webcpp/http/HttpTypes.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/beast/http/field.hpp>



BOOST_AUTO_TEST_SUITE(RequestTest)

BOOST_AUTO_TEST_CASE(POSTTwoKeys)
{
	http::request_t _request;
	
	_request.method(boost::beast::http::verb::post);
	_request.set(boost::beast::http::field::content_type, "application/x-www-form-urlencoded");
	_request.set_body("name=Dima&surname=Korotov");

	const auto& POST = std::get<http::request_t::key_value_t>(_request.POST());

	BOOST_TEST(POST.at("name") == "Dima");
	BOOST_TEST(POST.at("surname") == "Korotov");
}

BOOST_AUTO_TEST_CASE(POSTWithSpaces)
{
	http::request_t _request;

	_request.method(boost::beast::http::verb::post);
	_request.set(boost::beast::http::field::content_type, "application/x-www-form-urlencoded");
	_request.set_body("na+me=Dima+Korotov+++HAHA&sur+++name=+++Koro+tov+++");

	const auto& POST = std::get<http::request_t::key_value_t>(_request.POST());

	BOOST_TEST(POST.at("na me") == "Dima Korotov   HAHA");
	BOOST_TEST(POST.at("sur   name") == "   Koro tov   ");
}

BOOST_AUTO_TEST_SUITE_END()