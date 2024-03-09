#include "dictionary_functions.h"

std::optional<std::string> ParseArguments(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	std::optional<std::string> dictionaryPath = ParseArguments(argc, argv);

	try
	{
		RunDictionary(std::cin, std::cout, dictionaryPath);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}

std::optional<std::string> ParseArguments(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return std::string(argv[1]);
}