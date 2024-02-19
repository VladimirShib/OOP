#include "vector_functions.h"

int main()
{
	try
	{
		std::vector<double> numbers = ReadInputNumbers(std::cin);
		MultiplyVectorByMinElement(numbers);
		SortAndPrintVector(std::cout, numbers);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}