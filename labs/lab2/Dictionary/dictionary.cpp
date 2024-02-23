#include "dictionary_functions.h"

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