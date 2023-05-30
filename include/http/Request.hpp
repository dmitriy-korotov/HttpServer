#pragma once
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "http/Defines.hpp"
#include "http/QueryStringParser.hpp"

#include <boost/beast/http/message.hpp>
#include <boost/url/parse.hpp>

#include <string>
#include <unordered_map>



namespace http
{
	namespace beast_http = boost::beast::http;



	template <typename Body, typename Fields>
	class Request final : public beast_http::request<Body, Fields>
	{
	private:

		using Parent_t = beast_http::request<Body, Fields>;

	public:

		using QueryString = request::url::QSparser::query_string_t;



		Request() = default;
		Request(Request&&) = default;
		Request& operator=(Request&&) = default;
		
		Request(const Parent_t& _request);
		Request& operator=(const Parent_t& _other);
		Request(Parent_t&& _request) noexcept;
		Request& operator=(Parent_t&& _other) noexcept;


		operator Parent_t() noexcept;
		operator Parent_t&() noexcept;

		QueryString GET() noexcept;
		const QueryString& GET() const noexcept;
		
	private:

		void __set_query_string() const noexcept;

	private:
		
		mutable QueryString query_string_;

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
	void Request<Body, Fields>::__set_query_string() const noexcept
	{
		if (query_string_.empty())
		{
			request::url::QSparser qs_parser_(Parent_t::target());
			query_string_ = std::move(qs_parser_.get());
		}
	}



	template <typename Body, typename Fields>
	Request<Body, Fields>::template QueryString Request<Body, Fields>::GET() noexcept
	{
		__set_query_string();
		return query_string_;
	}



	template <typename Body, typename Fields>
	const Request<Body, Fields>::template QueryString& Request<Body, Fields>::GET() const noexcept
	{
		__set_query_string();
		return query_string_;
	}
}

#endif // !REQUEST_HPP
