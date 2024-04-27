#pragma once

#include <iostream>
#include <string>

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21,
};

class HttpUrl
{
public:
	HttpUrl(const std::string& url);
	HttpUrl(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP);
	HttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	void ParseURL(const std::string& url);

private:
	Protocol m_protocol;
	std::string m_url;
	std::string m_domain;
	int m_port;
	std::string m_document;
};

std::ostream& operator<<(std::ostream& os, const Protocol protocol);