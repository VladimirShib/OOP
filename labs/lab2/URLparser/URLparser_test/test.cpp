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

	{
		std::string line5 = "http://www.mysite.com:1/document/";
		CHECK(ParseUrl(url, line5));
		CHECK(url.fullUrl == line5);
		CHECK(url.host == "www.mysite.com");
		CHECK(url.port == 1);
		CHECK(url.document == "document/");
	}

	{
		std::string line6 = "http://www.mysite.com:65535/document/";
		CHECK(ParseUrl(url, line6));
		CHECK(url.fullUrl == line6);
		CHECK(url.host == "www.mysite.com");
		CHECK(url.port == 65535);
		CHECK(url.document == "document/");
	}

	{
		std::string line7 = "http://a.com/abc:8080";
		CHECK(ParseUrl(url, line7));
		CHECK(url.fullUrl == line7);
		CHECK(url.host == "a.com");
		CHECK(url.port == 80);
		CHECK(url.document == "abc:8080");
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
		std::string line2 = "http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title";
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

	{
		std::string line5 = "http://a.com:/abc:8080";
		CHECK(!ParseUrl(url, line5));
	}

	{
		std::string line6 = "http://a.com::/abc";
		CHECK(!ParseUrl(url, line6));
	}

	{
		std::string line7 = "http://a.com:100:/abc";
		CHECK(!ParseUrl(url, line7));
	}
}