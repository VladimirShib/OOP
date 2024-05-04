#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../FindMaxEx.h"
#include <cstring>
#include <stdexcept>
#include <string>

namespace
{

struct Sportsman
{
	std::string name;
	float height = 0.f;
	float weight = 0.f;
};

} // namespace

SCENARIO("Testing with integers")
{
	GIVEN("Vector of integers")
	{
		std::vector<int> vec = { 4, 8, 15, 16, 23, 42 };

		WHEN("Searching for max element")
		{
			int max = 0;
			bool result = FindMaxEx(vec, max, [](int a, int b) { return a < b; });

			THEN("Function returns true")
			{
				CHECK(result);
				CHECK(max == 42);
			}
		}
	}

	GIVEN("Vector of negative integers")
	{
		std::vector<int> vec = { -5, -24, -325, -1, -1, -9, -73 };

		WHEN("Searching for max element")
		{
			int max = 0;
			bool result = FindMaxEx(vec, max, [](int a, int b) { return a < b; });

			THEN("Function returns true")
			{
				CHECK(result);
				CHECK(max == -1);
			}
		}
	}

	GIVEN("Vector with one element")
	{
		std::vector<int> vec = { 10 };

		WHEN("Searching for max element")
		{
			int max = 0;
			bool result = FindMaxEx(vec, max, [](int a, int b) { return a < b; });

			THEN("Function returns true")
			{
				CHECK(result);
				CHECK(max == 10);
			}
		}
	}

	GIVEN("Empty vector")
	{
		std::vector<int> vec;

		WHEN("Searching for max element")
		{
			int max = 0;
			bool result = FindMaxEx(vec, max, [](int a, int b) { return a < b; });

			THEN("Function returns false")
			{
				CHECK_FALSE(result);
			}
		}
	}
}

SCENARIO("Testing with float point numbers")
{
	GIVEN("Vector of float point numbers")
	{
		std::vector<float> vec = { 52.52f, 84.39f, 9.29f, 482.495f, 39.32f, 482.496f, 305.2f, 10.255f };

		WHEN("Searching for max element")
		{
			float max = 0;
			bool result = FindMaxEx(vec, max, [](float a, float b) { return a < b; });

			THEN("Function returns true")
			{
				CHECK(result);
				CHECK(max == 482.496f);
			}
		}
	}
}

SCENARIO("Testing with strings")
{
	GIVEN("Vector of strings")
	{
		std::vector<std::string> vec = { "aabb", "aaab", "abba", "abaaaaa" };

		WHEN("Searching for max element")
		{
			std::string max;
			bool result = FindMaxEx(vec, max, [](std::string a, std::string b) { return a < b; });

			THEN("Function returns true")
			{
				CHECK(result);
				CHECK(max == "abba");
			}
		}
	}
}

SCENARIO("Testing with C-style strings")
{
	GIVEN("Vector of pointers to strings")
	{
		const char* great = "great";
		const char* greater = "greater";
		const char* greatest = "greatest";
		std::vector<const char*> vec = { great, greatest, greater };

		WHEN("Searching for max element")
		{
			const char* max;
			bool result = FindMaxEx(vec, max, [](const char* a, const char* b) { return a < b; });

			THEN("Function returns true")
			{
				CHECK(result);
				CHECK(max == "greatest");
			}
		}
	}
}

SCENARIO("Testing with structs")
{
	GIVEN("Vector of structs")
	{
		std::vector<Sportsman> sportsmen = {
			{ "first", 170.5f, 70.5f },
			{ "second", 180.7f, 81.1f },
			{ "tallest", 199.9f, 100.6f },
			{ "fourth", 165.1f, 67.7f },
			{ "heaviest", 190.4f, 110.3f }
		};

		WHEN("Searching for tallest and heaviest sportsmen")
		{
			Sportsman tallest;
			Sportsman heaviest;

			auto LessHeight = [](const Sportsman& first, const Sportsman& second) {
				return first.height < second.height;
			};
			auto LessWeight = [](const Sportsman& first, const Sportsman& second) {
				return first.weight < second.weight;
			};

			bool result1 = FindMaxEx(sportsmen, tallest, LessHeight);
			bool result2 = FindMaxEx(sportsmen, heaviest, LessWeight);

			THEN("Function works fine")
			{
				CHECK(result1);
				CHECK(result2);
				CHECK(tallest.name == "tallest");
				CHECK(heaviest.name == "heaviest");
			}
		}
	}
}

SCENARIO("Testing with exception")
{
	GIVEN("Vector of structs")
	{
		std::vector<Sportsman> sportsmen = {
			{ "first", 170.5f, 70.5f },
			{ "second", 180.7f, 81.1f },
			{ "tallest", 199.9f, 100.6f },
			{ "fourth", 165.1f, 67.7f },
			{ "heaviest", 190.4f, 110.3f }
		};

		WHEN("Searching for tallest and heaviest sportsmen, but one function throws exception")
		{
			Sportsman tallest;
			Sportsman heaviest;

			auto LessHeight = [](const Sportsman& first, const Sportsman& second) {
				return first.height < second.height;
			};
			auto LessWeight = [](const Sportsman& first, const Sportsman& second) {
				throw std::runtime_error("");
				return first.weight < second.weight;
			};

			bool result1 = FindMaxEx(sportsmen, tallest, LessHeight);
			bool result2 = false;
			CHECK_THROWS(result2 = FindMaxEx(sportsmen, heaviest, LessWeight));

			THEN("Function works fine, max value for second function doesn't change")
			{
				CHECK(result1);
				CHECK(!result2);
				CHECK(tallest.name == "tallest");
				CHECK(heaviest.name == "");
			}
		}
	}
}