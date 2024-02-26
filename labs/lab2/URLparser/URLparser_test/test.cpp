#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../parser_functions.h"

TEST_CASE("Valid URLs")
{
	URL url = { "", "", 0, "" };

	{
		std::string line1 = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		CHECK(ParseUrl(url, line1));
		CHECK(url.fullUrl == line1);
		CHECK(url.host == "www.mysite.com");
		CHECK(url.port == 80);
		CHECK(url.document == "docs/document1.html?page=30&lang=en#title");
	}

	{
		std::string line2 = "http://www.mysite.com:8080";
		CHECK(ParseUrl(url, line2));
		CHECK(url.fullUrl == line2);
		CHECK(url.host == "www.mysite.com");
		CHECK(url.port == 8080);
		CHECK(url.document == "");
	}

	{
		std::string line3 = "https://www.mysite.com:8080/document/";
		CHECK(ParseUrl(url, line3));
		CHECK(url.fullUrl == line3);
		CHECK(url.host == "www.mysite.com");
		CHECK(url.port == 8080);
		CHECK(url.document == "document/");
	}

	{
		std::string line4 = "ftp://www.mysite.com/lang=en#title";
		CHECK(ParseUrl(url, line4));
		CHECK(url.fullUrl == line4);
		CHECK(url.host == "www.mysite.com");
		CHECK(url.port == 21);
		CHECK(url.document == "lang=en#title");
	}
}

TEST_CASE("Invalid URLs")
{
	URL url = { "", "", 0, "" };

	{
		std::string line1 = "http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title";
		CHECK(!ParseUrl(url, line1));
	}

	{
		std::string line2 = "http://www.mysite.com:0000/docs/document1.html?page=30&lang=en#title";
		CHECK(!ParseUrl(url, line2));
	}

	{
		std::string line3 = "httpp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		CHECK(!ParseUrl(url, line3));
	}

	{
		std::string line4 = "http:///www.mysite.com";
		CHECK(!ParseUrl(url, line4));
	}
}