#include "primeNumbers_functions.h"
#include <stdexcept>
#include <string>

int ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	try
	{
		int number = ParseArgs(argc, argv);
		std::set<int> primeNumbers = GeneratePrimeNumbersSet(number);
		PrintSet(std::cout, primeNumbers);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}

int ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid argument count\nUsage: primeNumbers.exe <number>");
	}

	int number = std::stoi(std::string(argv[1]));

	if (number < 0 || number > 100000000)
	{
		throw std::invalid_argument("Number should be in range [0; 100000000]");
	}

	return number;
}