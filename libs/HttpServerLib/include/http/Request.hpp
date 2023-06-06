#pragma once

#include <http/QueryStringParser.hpp>
#include <http/ContentTypeConvertings.hpp>

#include <boost/beast/http/message.hpp>

#include <string>
#include <unordered_map>
#include <variant>



namespace http
{
	namespace beast_http = boost::beast::http;



	template <typename Body, typename Fields>
	class Request final : public beast_http::request<Body, Fields>
	{
	private:

		using Parent_t = beast_http::request<Body, Fields>;

	public:

		using key_value_t = std::unordered_map<std::string, std::string>;
		using multipart_from_data_t = std::unordered_map<std::string, std::pair<std::string, std::string>>;
		using QueryString = request::url::QSparser::query_string_t;
		using POST_t = std::variant<std::string, key_value_t, multipart_from_data_t>;



		Request() = default;
		Request(Request&&) = default;
		Request& operator=(Request&&) = default;
		
		Request(const Parent_t& _request);
		Request& operator=(const Parent_t& _other);
		Request(Parent_t&& _request) noexcept;
		Request& operator=(Parent_t&& _other) noexcept;


		operator Parent_t() noexcept;
		operator Parent_t&() noexcept;

		QueryString& GET();
		const QueryString& GET() const;

		POST_t& POST();
		const POST_t& POST() const;

	private:

		void __set_query_string() const;
		void __set_post_body() const;

	private:
		
		mutable QueryString query_string_;
		mutable POST_t POST_body_;

	};





	template <typename Body, typename Fields>
	Request<Body, Fields>::Request(const Parent_t& _request)
			: Parent_t(_request)
	{}



	template <typename Body, typename Fields>
	Request<Body, Fields>& Request<Body, Fields>::operator=(const Parent_t& _other)
	{
		static_cast<Parent_t>(*this) = _other;
		return *this;
	}



	template <typename Body, typename Fields>
	Request<Body, Fields>::Request(Parent_t&& _request) noexcept
		: Parent_t(std::move(_request))
	{}



	template <typename Body, typename Fields>
	Request<Body, Fields>& Request<Body, Fields>::operator=(Parent_t&& _other) noexcept
	{
		static_cast<Parent_t>(*this) = std::move(_other);
		return *this;
	}



	template <typename Body, typename Alloc>
	Request<Body, Alloc>::operator Parent_t() noexcept
	{
		return static_cast<Parent_t>(*this);
	}



	template <typename Body, typename Alloc>
	Request<Body, Alloc>::operator Parent_t&() noexcept
	{
		return static_cast<Parent_t&>(*this);
	}



	template <typename Body, typename Fields>
	void Request<Body, Fields>::__set_query_string() const
	{
		if (query_string_.empty() && Parent_t::method() == beast_http::verb::get)
		{
			request::url::QSparser qs_parser_(Parent_t::target());
			query_string_ = std::move(qs_parser_.get());
		}
	}



	template <typename Body, typename Fields>
	Request<Body, Fields>::template QueryString& Request<Body, Fields>::GET()
	{
		__set_query_string();
		return query_string_;
	}



	template <typename Body, typename Fields>
	const Request<Body, Fields>::template QueryString& Request<Body, Fields>::GET() const
	{
		__set_query_string();
		return query_string_;
	}



	template <typename Body, typename Fields>
	void Request<Body, Fields>::__set_post_body() const
	{
		if (query_string_.empty() && Parent_t::method() == beast_http::verb::post)
		{
			auto content_type = Parent_t::get(beast_http::field::content_type);
		}
	}



	template <typename Body, typename Fields>
	Request<Body, Fields>::template POST_t& Request<Body, Fields>::POST()
	{

	}



	template <typename Body, typename Fields>
	const Request<Body, Fields>::template POST_t& Request<Body, Fields>::POST() const
	{
		
	}
}