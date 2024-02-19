#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../vector_functions.h"

// Testing `ReadInputNumbers(std::istream&)` function
TEST_CASE("Reading input")
{
	SECTION("Valid input")
	{
		std::string input = "6 2.1 85 3223 53";
		std::istringstream iss(input);
		std::vector<double> v = ReadInputNumbers(iss);

		std::vector<double> expectedVector = { 6, 2.1, 85, 3223, 53 };
		CHECK(v == expectedVector);
	}

	//SECTION("Invalid input")
	//{
	//	std::string input = "6 2.1 85 3223 53 hello";
	//	std::istringstream iss(input);
	//	std::vector<double> v = ReadInputNumbers(iss);

	//	CHECK_THROWS(ReadInputNumbers(iss));
	//}
}

// Testing `MultiplyVectorByMinElement(std::vector<double>&)` function
TEST_CASE("Empty vector")
{
	std::vector<double> inputVector = {};
	std::vector<double> expectedVector = {};
	MultiplyVectorByMinElement(inputVector);

	CHECK(inputVector == expectedVector);
}

TEST_CASE("Min value 0")
{
	std::vector<double> inputVector = { 99.0943, 95.58404, 54.58, 86.2901, 56, 39.58618, 0, 38.01, 4.0486, 98.541 };
	std::vector<double> expectedVector = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	MultiplyVectorByMinElement(inputVector);

	CHECK(inputVector == expectedVector);
}

TEST_CASE("Min value 1")
{
	std::vector<double> inputVector = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::vector<double> expectedVector = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	MultiplyVectorByMinElement(inputVector);

	CHECK(inputVector == expectedVector);
}

TEST_CASE("Negative min value")
{
	std::vector<double> inputVector = { 32.18, 75.8, 64.046, -33.52, 32.3, 81.307, -15.8, 71.34, 76.96, -82.6 };
	std::vector<double> expectedVector = { -2658.068, -6261.08, -5290.1996, 2768.752, -2667.98, -6715.9582, 1305.08, -5892.684, -6356.896, 6822.76 };
	MultiplyVectorByMinElement(inputVector);
	CHECK_THAT(inputVector, Catch::Approx(expectedVector));
}

// Testing `SortAndPrintVector(std::ostream&, std::vector<double>&)` function
TEST_CASE("Printing vector")
{
	SECTION("Sorted vector")
	{
		std::vector<double> inputVector = { 0, 1, 2, 3, 4, 5 };
		std::string expectedOutput = "0.000 1.000 2.000 3.000 4.000 5.000 \n";

		std::ostringstream oss;
		SortAndPrintVector(oss, inputVector);
		std::string result = oss.str();

		CHECK(result == expectedOutput);
	}
}