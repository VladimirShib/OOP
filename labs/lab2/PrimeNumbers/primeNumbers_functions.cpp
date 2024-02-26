#include "primeNumbers_functions.h"

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

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primeNumbers;

	if (upperBound < 2)
	{
		return primeNumbers;
	}
	primeNumbers.insert(2);

	std::vector<bool> sieve(upperBound + 1, true);

	for (auto index = 3; index <= upperBound; index += 2)
	{
		if (sieve[index])
		{
			primeNumbers.insert(primeNumbers.end(), index);

			if (index < std::sqrt(upperBound))
			{
				for (auto i = index * index; i <= upperBound; i += index)
				{
					sieve[i] = false;
				}
			}
		}
	}

	return primeNumbers;
}

void PrintSet(std::ostream& output, const std::set<int>& primes)
{
	for (int number : primes)
	{
		output << number << " ";
	}
}