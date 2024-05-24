#include "MyList.h"
#include <iostream>
#include <string>

struct MyStruct
{
	MyStruct(int data)
		: m_data(data)
	{
	}

	int m_data;
};

int main()
{
	try
	{
		MyList<int> listOfIntegers = { 1, 2, 3 };
		for (auto el : listOfIntegers)
		{
			std::cout << el << " ";
		}

		std::cout << "\n";

		MyList<std::string> listOfStrings = { "one", "two", "three" };
		for (const auto& el : listOfStrings)
		{
			std::cout << el << " ";
		}

		std::cout << "\n";

		MyStruct st1(42);
		MyStruct st2(43);
		MyList<MyStruct> listOfMyStructs = { st1, st2 };
		for (const auto el : listOfMyStructs)
		{
			std::cout << el.m_data << " ";
		}

		std::cout << "\n";
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
	}

	return 0;
}