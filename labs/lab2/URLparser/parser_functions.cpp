#include "parser_functions.h"

bool ParseUrl(URL& url, const std::string& str)
{
	std::regex urlRegex(R"((\w+):\/\/([^\/:]+)(?::(\d+))?\/?(.*?))");
	std::smatch result;

	if (std::regex_match(str, result, urlRegex))
	{
		if (SaveData(url, result))
		{
			return true;
		}
	}

	return false;
}

bool SaveData(URL& url, const std::smatch& result)
{
	std::string protocol;
	if (!GetProtocol(result[1], protocol))
	{
		return false;
	}

	url.fullUrl = result[0];
	url.host = result[2];
	url.document = result[4];

	if (result[3].matched)
	{
		int port = std::stoi(result[3]);

		if (port < 1 || port > 65535)
		{
			return false;
		}
		url.port = port;
	}
	else
	{
		url.port = GetDefaultPort(protocol);
	}

	return true;
}

bool GetProtocol(std::string result, std::string& protocol)
{
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char ch) { return std::tolower(ch); });

	if (result == "http" || result == "https" || result == "ftp")
	{
		protocol = result;

		return true;
	}

	return false;
}

int GetDefaultPort(const std::string& protocol)
{
	if (protocol == "http")
	{
		return static_cast<int>(Protocol::HTTP);
	}
	else if (protocol == "https")
	{
		return static_cast<int>(Protocol::HTTPS);
	}
	else
	{
		return static_cast<int>(Protocol::FTP);
	}
}

void PrintUrl(std::ostream& output, const URL& url)
{
	output << "\nURL: " << url.fullUrl << "\n";
	output << "HOST: " << url.host << "\n";
	output << "PORT: " << url.port << "\n";
	output << "DOC: " << url.document << "\n\n";
}