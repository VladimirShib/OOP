#include "vector_functions.h"

std::vector<double> ReadInputNumbers(std::istream& input)
{
	std::vector<double> numbers;
	double number;

	while (input >> number)
	{
		numbers.push_back(number);
	}

	if (!input.eof())
	{
		throw std::invalid_argument("Invalid input. Please enter numeric values.");
	}
	input.clear();

	return numbers;
}

void MultiplyVectorByMinElement(std::vector<double>& numbers)
{
	if (!numbers.empty())
	{
		auto minElementIterator = std::min_element(numbers.begin(), numbers.end());
		double minElement = *minElementIterator;

		for (double& number : numbers)
		{
			number *= minElement;
		}
	}
}

void SortAndPrintVector(std::ostream& output, std::vector<double>& numbers)
{
	if (!numbers.empty())
	{
		std::sort(numbers.begin(), numbers.end());

		for (double number : numbers)
		{
			output << std::fixed << std::setprecision(3) << number << " ";
		}
		output << "\n";
	}
}