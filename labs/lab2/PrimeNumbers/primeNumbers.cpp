#include "primeNumbers_functions.h"

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