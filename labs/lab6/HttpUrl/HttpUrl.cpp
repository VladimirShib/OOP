#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <algorithm>
#include <cctype>
#include <regex>

namespace
{

Protocol ParseProtocol(const std::string& protocol)
{
	std::string result(protocol);
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char ch) { return std::tolower(ch); });

	if (result == "http")
	{
		return Protocol::HTTP;
	}
	if (result == "https")
	{
		return Protocol::HTTPS;
	}
	if (result == "ftp")
	{
		return Protocol::FTP;
	}

	throw UrlParsingError("Invalid protocol");
}

unsigned short ParsePort(const std::string& portStr)
{
	if (portStr.empty())
	{
		throw UrlParsingError("Invalid port");
	}
	for (char ch : portStr)
	{
		if (!std::isdigit(ch))
		{
			throw UrlParsingError("Invalid port");
		}
	}

	int port = std::stoi(portStr);
	if (port < 1 || port > 65535)
	{
		throw UrlParsingError("Invalid port");
	}

	return static_cast<unsigned short>(port);
}

std::string ParseDocument(const std::string& document)
{
	if (document.empty() || document[0] != '/')
	{
		return "/" + document;
	}

	return document;
}

bool IsDefaultPort(unsigned short port, Protocol protocol)
{
	return port == static_cast<unsigned short>(protocol);
}

std::string ComposeURL(Protocol protocol, const std::string& domain, unsigned short port, const std::string& document)
{
	std::string url;

	switch (protocol)
	{
	case Protocol::HTTP:
		url += "http://";
		break;
	case Protocol::HTTPS:
		url += "https://";
		break;
	case Protocol::FTP:
		url += "ftp://";
		break;
	default:
		break;
	}

	url += domain == "/" ? "" : domain;
	url += IsDefaultPort(port, protocol) ? "" : ":" + std::to_string(port);
	url += document;

	if (url.back() == '/')
	{
		url.pop_back();
	}

	return url;
}

} // namespace

HttpUrl::HttpUrl(const std::string& url)
{
	ParseURL(url);
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
	: HttpUrl(domain, document, protocol, static_cast<unsigned short>(protocol))
{
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
	if (domain.empty())
	{
		throw UrlParsingError("Invalid URL");
	}

	if (port < 1 || port > 65535)
	{
		throw UrlParsingError("Invalid port");
	}

	m_protocol = protocol;
	m_domain = domain;
	m_port = port;
	m_document = ::ParseDocument(document);
	m_url = ::ComposeURL(m_protocol, m_domain, m_port, m_document);
}

std::string HttpUrl::GetURL() const
{
	return m_url;
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short HttpUrl::GetPort() const
{
	return m_port;
}

void HttpUrl::ParseURL(const std::string& url)
{
	std::regex urlRegex(R"((\w+):\/\/([^\/:]+)(?::([^\/]*))?\/?(.*?))");
	std::smatch result;

	if (!std::regex_match(url, result, urlRegex))
	{
		throw UrlParsingError("Ivalid URL");
	}

	m_protocol = ::ParseProtocol(result[1]);
	m_port = result[3].matched ? ::ParsePort(result[3]) : static_cast<unsigned short>(m_protocol);
	m_domain = result[2];
	m_document = ::ParseDocument(result[4]);
	m_url = ::ComposeURL(m_protocol, m_domain, m_port, m_document);
}

std::ostream& operator<<(std::ostream& os, const Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return os << "HTTP";
	case Protocol::HTTPS:
		return os << "HTTPS";
	case Protocol::FTP:
		return os << "FTP";
	default:
		return os << "No protocol";
	}
}