#include "HttpUrl.h"
#include "UrlParsingError.h"

int main()
{
	std::string line;

	while (std::getline(std::cin, line))
	{
		try
		{
			HttpUrl url(line);

			std::cout << "URL: " << url.GetURL() << "\n";
			std::cout << "Protocol: " << url.GetProtocol() << "\n";
			std::cout << "Domain: " << url.GetDomain() << "\n";
			std::cout << "Port: " << url.GetPort() << "\n";
			std::cout << "Document: " << url.GetDocument() << "\n\n";
		}
		catch (const UrlParsingError& ex)
		{
			std::cout << ex.what() << '\n';
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << '\n';
		}
	}

	return 0;
}