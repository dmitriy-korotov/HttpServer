#pragma once
#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <http/Defines.hpp>

#include <boost/beast/http/message.hpp>



namespace http
{
	namespace beast_http = boost::beast::http;



	template <typename Body, typename Fields>
	class Response final : public beast_http::response<Body, Fields>
	{
	private:

		using Parent_t = beast_http::response<Body, Fields>;

	public:

		Response() = default;
		Response(Response&&) = default;
		Response& operator=(Response&&) = default;

		Response(const Parent_t& _response);
		Response& operator=(const Parent_t& _other);
		Response(Parent_t&& _response) noexcept;
		Response& operator=(Parent_t&& _other) noexcept;

		operator Parent_t() noexcept;
		operator Parent_t& () noexcept;

	};





	template <typename Body, typename Fields>
	Response<Body, Fields>::Response(const Parent_t& _response)
		: Parent_t(_response)
	{}



	template <typename Body, typename Fields>
	Response<Body, Fields>& Response<Body, Fields>::operator=(const Parent_t& _other)
	{
		static_cast<Parent_t>(*this) = _other;
		return *this;
	}



	template <typename Body, typename Fields>
	Response<Body, Fields>::Response(Parent_t&& _response) noexcept
		: Parent_t(std::move(_response))
	{}



	template <typename Body, typename Fields>
	Response<Body, Fields>& Response<Body, Fields>::operator=(Parent_t&& _other) noexcept
	{
		static_cast<Parent_t>(*this) = std::move(_other);
		return *this;
	}



	template <typename Body, typename Alloc>
	Response<Body, Alloc>::operator Parent_t() noexcept
	{
		return static_cast<Parent_t>(*this);
	}



	template <typename Body, typename Alloc>
	Response<Body, Alloc>::operator Parent_t& () noexcept
	{
		return static_cast<Parent_t&>(*this);
	}
}

#endif // !RESPONSE_HPP
