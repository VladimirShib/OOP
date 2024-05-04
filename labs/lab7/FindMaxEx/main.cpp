#include "FindMaxEx.h"
#include <iostream>
#include <string>

struct Sportsman
{
	std::string name;
	float height = 0.f;
	float weight = 0.f;
};

int main()
{
	std::vector<Sportsman> sportsmen = {
		{ "first", 170.5f, 70.5f },
		{ "second", 180.7f, 81.1f },
		{ "third", 199.9f, 100.6f },
		{ "fourth", 165.1f, 67.7f },
		{ "fifth", 190.4f, 110.3f }
	};

	Sportsman tallest;
	Sportsman heaviest;

	auto LessHeight = [](const Sportsman& first, const Sportsman& second) {
		return first.height < second.height;
	};
	auto LessWeight = [](const Sportsman& first, const Sportsman& second) {
		return first.weight < second.weight;
	};

	if (FindMaxEx(sportsmen, tallest, LessHeight))
	{
		std::cout << "Tallest sportsman: " << tallest.name << "\n";
	}

	if (FindMaxEx(sportsmen, heaviest, LessWeight))
	{
		std::cout << "Heaviest sportsman: " << heaviest.name << "\n";
	}

	return 0;
}