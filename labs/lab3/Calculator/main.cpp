#include "calculatorApp.h"
#include "calculatorEngine.h"

int main()
{
	CCalculatorEngine engine;
	CCalculatorApp app(engine, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!app.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}

	return 0;
}