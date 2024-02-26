#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../primeNumbers_functions.h"

TEST_CASE("Checking contents")
{
	CHECK(GeneratePrimeNumbersSet(2) == std::set<int>{ 2 });
	CHECK(GeneratePrimeNumbersSet(3) == std::set<int>{ 2, 3 });
	CHECK(GeneratePrimeNumbersSet(6) == std::set<int>{ 2, 3, 5 });
	CHECK(GeneratePrimeNumbersSet(7) == std::set<int>{ 2, 3, 5, 7 });
	CHECK(GeneratePrimeNumbersSet(36) == std::set<int>{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 });
	CHECK(GeneratePrimeNumbersSet(37) == std::set<int>{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 });
	CHECK(GeneratePrimeNumbersSet(100) == std::set<int>{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 });
	CHECK(GeneratePrimeNumbersSet(101) == std::set<int>{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101 });
}

TEST_CASE("Checking size")
{
	CHECK(GeneratePrimeNumbersSet(100).size() == 25);
	CHECK(GeneratePrimeNumbersSet(101).size() == 26);
	CHECK(GeneratePrimeNumbersSet(149).size() == 35);
	CHECK(GeneratePrimeNumbersSet(150).size() == 35);
	CHECK(GeneratePrimeNumbersSet(151).size() == 36);
	CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}