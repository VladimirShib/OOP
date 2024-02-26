#include "parser_functions.h"

int main(int argc, char* argv[])
{
	std::string line;

	while (std::cin >> line)
	{
		URL url = { "", "", 0, "" };

		if (ParseUrl(url, line))
		{
			PrintUrl(std::cout, url);
		}
		else
		{
			std::cout << "Invalid URL\n\n";
		}
	}

	return 0;
}