#include "vector_functions.h"
#include <algorithm>
#include <iomanip>

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
	if (numbers.empty())
	{
		return;
	}
	
	auto minElementIterator = std::min_element(numbers.begin(), numbers.end());
	double minElement = *minElementIterator;

	std::transform(numbers.begin(), numbers.end(),
				   numbers.begin(),
				   [minElement](double number) { return number * minElement; });
}

void SortVector(std::vector<double>& numbers)
{
	std::sort(numbers.begin(), numbers.end());
}

void PrintVector(std::ostream& output, const std::vector<double>& numbers)
{
	if (numbers.empty())
	{
		return;
	}

	for (double number : numbers)
	{
		output << std::fixed << std::setprecision(3) << number << " ";
	}
	output << std::endl;
}