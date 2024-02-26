#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../polishNotation_functions.h"

TEST_CASE("Valid expressions")
{
	std::string line;

	{
		line = "(+ 7)";
		CHECK(CaculateExpression(line) == 7);
	}
	{
		line = "(* 8)";\
		CHECK(CaculateExpression(line) == 8);
	}
	{
		line = "(+ 2 3)";
		CHECK(CaculateExpression(line) == 5);
	}
	{
		line = "(+ 2 3 4)";
		CHECK(CaculateExpression(line) == 9);
	}
	{
		line = "(* 2 4)";
		CHECK(CaculateExpression(line) == 8);
	}
	{
		line = "(* 2 3 4)";
		CHECK(CaculateExpression(line) == 24);
	}
	{
		line = "(+ (* 2 3) (* 3 4))";
		CHECK(CaculateExpression(line) == 18);
	}
	{
		line = "(* (+ 1 2) (+ 3 1))";
		CHECK(CaculateExpression(line) == 12);
	}
	{
		line = "(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2) ))";
		CHECK(CaculateExpression(line) == 33);
	}
	{
		line = "(+ -2 3)";
		CHECK(CaculateExpression(line) == 1);
	}
}

TEST_CASE("Invalid expressions")
{
	std::string line;

	{
		line = "()";
		CHECK_THROWS(CaculateExpression(line));
	}
	{
		line = "(+)";
		CHECK_THROWS(CaculateExpression(line));
	}
	{
		line = "(+ 1())";
		CHECK_THROWS(CaculateExpression(line));
	}
	{
		line = "(+ 1(* 2)";
		CHECK_THROWS(CaculateExpression(line));
	}
	{
		line = "(+ a)";
		CHECK_THROWS(CaculateExpression(line));
	}
	{
		line = "(+ 5";
		CHECK_THROWS(CaculateExpression(line));
	}
	{
		line = "(- 1 2)";
		CHECK_THROWS(CaculateExpression(line));
	}
}