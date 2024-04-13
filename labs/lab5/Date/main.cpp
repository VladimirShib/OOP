#include "Date.h"
#include <iostream>

int main()
{
	CDate date(12, Month::APRIL, 2024);

	std::cout << date << "\n";
	std::cout << date.GetWeekDay() << "\n";
	std::cout << date.GetMonth() << "\n";

	return 0;
}