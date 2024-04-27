#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../HttpUrl.h"
#include "../UrlParsingError.h"

SCENARIO("Testing full url constructor")
{
	WHEN("URL is valid")
	{
		THEN("Class instance is created")
		{
			HttpUrl url("http://www.mysite.com:80/docs/document1.html?page=30&lang=en#title");

			CHECK(url.GetURL() == "http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetDomain() == "www.mysite.com");
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDocument() == "/docs/document1.html?page=30&lang=en#title");
		}

		THEN("Class instance is created")
		{
			HttpUrl url("http://www.mysite.com:8080");

			CHECK(url.GetURL() == "http://www.mysite.com:8080");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetDomain() == "www.mysite.com");
			CHECK(url.GetPort() == 8080);
			CHECK(url.GetDocument() == "/");
		}

		THEN("Class instance is created")
		{
			HttpUrl url("https://www.mysite.com:8080/document");

			CHECK(url.GetURL() == "https://www.mysite.com:8080/document");
			CHECK(url.GetProtocol() == Protocol::HTTPS);
			CHECK(url.GetDomain() == "www.mysite.com");
			CHECK(url.GetPort() == 8080);
			CHECK(url.GetDocument() == "/document");
		}

		THEN("Class instance is created")
		{
			HttpUrl url("ftp://www.mysite.com/lang=en#title");

			CHECK(url.GetURL() == "ftp://www.mysite.com/lang=en#title");
			CHECK(url.GetProtocol() == Protocol::FTP);
			CHECK(url.GetDomain() == "www.mysite.com");
			CHECK(url.GetPort() == 21);
			CHECK(url.GetDocument() == "/lang=en#title");
		}

		THEN("Class instance is created")
		{
			HttpUrl url("http://www.mysite.com:1/document");

			CHECK(url.GetURL() == "http://www.mysite.com:1/document");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetDomain() == "www.mysite.com");
			CHECK(url.GetPort() == 1);
			CHECK(url.GetDocument() == "/document");
		}

		THEN("Class instance is created")
		{
			HttpUrl url("http://www.mysite.com:65535/document");

			CHECK(url.GetURL() == "http://www.mysite.com:65535/document");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetDomain() == "www.mysite.com");
			CHECK(url.GetPort() == 65535);
			CHECK(url.GetDocument() == "/document");
		}

		THEN("Class instance is created")
		{
			HttpUrl url("http://a.com/abc:8080");

			CHECK(url.GetURL() == "http://a.com/abc:8080");
			CHECK(url.GetProtocol() == Protocol::HTTP);
			CHECK(url.GetDomain() == "a.com");
			CHECK(url.GetPort() == 80);
			CHECK(url.GetDocument() == "/abc:8080");
		}
	}

	WHEN("URL is invalid")
	{
		THEN("Exception is thrown")
		{
			CHECK_THROWS_AS(HttpUrl("http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
		}
	}

	WHEN("URL is invalid")
	{
		THEN("Exception is thrown")
		{
			CHECK_THROWS_AS(HttpUrl("http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
		}
	}

	WHEN("URL is invalid")
	{
		THEN("Exception is thrown")
		{
			CHECK_THROWS_AS(HttpUrl("httpp://www.mysite.com/docs/document1.html?page=30&lang=en#title"), UrlParsingError);
		}
	}

	WHEN("URL is invalid")
	{
		THEN("Exception is thrown")
		{
			CHECK_THROWS_AS(HttpUrl("http:///www.mysite.com"), UrlParsingError);
		}
	}

	WHEN("URL is invalid")
	{
		THEN("Exception is thrown")
		{
			CHECK_THROWS_AS(HttpUrl("http://a.com:/abc:8080"), UrlParsingError);
		}
	}

	WHEN("URL is invalid")
	{
		THEN("Exception is thrown")
		{
			CHECK_THROWS(HttpUrl("http://a.com::/abc"));
		}
	}

	WHEN("URL is invalid")
	{
		THEN("Exception is thrown")
		{
			CHECK_THROWS_AS(HttpUrl("http://a.com:100:/abc"), UrlParsingError);
		}
	}
}