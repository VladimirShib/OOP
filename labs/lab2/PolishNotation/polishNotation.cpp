#include "polishNotation_functions.h"

int main(int argc, char* argv[])
{
	try
	{
		std::string line;

		while (std::getline(std::cin, line))
		{
			int result = CaculateExpression(line);
			std::cout << "Result: " << result << "\n\n";
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}