#include "template_functions.h"
#include <iostream>
#include <stdexcept>

Args ParseArguments(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	try
	{
		Args args = ParseArguments(argc, argv);
		CopyFileWithReplacements(args);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}

Args ParseArguments(int argc, char* argv[])
{
	if (argc < 3 || argc % 2 == 0)
	{
		throw std::invalid_argument("Invalid argument count\n"
									"Usage: expandTemplate.exe <input-file> <output-file> [<key> <value> [<key> <value> …]]");
	}

	Args args;
	args.inputFileName = std::string(argv[1]);
	args.outputFileName = std::string(argv[2]);

	for (size_t i = 3; i < argc; i += 2)
	{
		std::string key = argv[i];
		if (key.empty())
		{
			continue;
		}

		std::string value = argv[i + 1];

		auto it = args.params.find(key);
		if (it != args.params.end() && it->second != value)
		{
			throw std::invalid_argument("Trying to replace existing value for " + key + " key!");
		}

		args.params[key] = value;
	}

	return args;
}