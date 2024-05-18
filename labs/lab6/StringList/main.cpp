#include "StringList.h"
#include <iostream>

int main()
{
	StringList list = { "one", "two", "three" };
	auto it = list.end();

	--it;
	std::cout << *it << "\n\n";

	auto size = it->size();

	try
	{
		for (const auto& el : list)
		{
			std::cout << el << "\n";
		}
		std::cout << "size: " << size << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}

	return 0;
}