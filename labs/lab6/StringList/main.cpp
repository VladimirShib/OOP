#include "StringList.h"
#include <iostream>

int main()
{
	StringList list = { "one", "two", "three" };
	auto it = list.end();

	--it;
	std::cout << *it << "\n\n";

	try
	{
		for (const auto& el : list)
		{
			std::cout << el << "\n";
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}

	return 0;
}