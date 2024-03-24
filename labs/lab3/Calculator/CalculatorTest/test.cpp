#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../calculatorEngine.h"
#include "../calculatorApp.h"
#include <cmath>
#include <limits>
#include <iostream>
#include <sstream>

SCENARIO("Testing calculator engine")
{
	GIVEN("Calculator")
	{
		CCalculatorEngine calculator;

		WHEN("Declaring a new value")
		{
			CHECK(calculator.DeclareVar("var1"));

			THEN("Variable will be created")
			{
				CHECK(calculator.GetValue("var1").has_value());
				CHECK(std::isnan(calculator.GetValue("var1").value()));
			}

			AND_WHEN("Declaring a value with existing name")
			{
				THEN("Variable won't be created")
				{
					CHECK(!calculator.DeclareVar("var1"));
				}
			}
		}

		WHEN("Defining a new value")
		{
			CHECK(calculator.DefineVarWithNumber("var1", "42"));

			THEN("Variable will be created")
			{
				CHECK(calculator.GetValue("var1").has_value());
				CHECK(calculator.GetValue("var1").value() == 42);
			}

			AND_WHEN("Redefining this variable")
			{
				CHECK(calculator.DefineVarWithNumber("var1", "43"));

				THEN("New value will be assigned")
				{
					CHECK(calculator.GetValue("var1").value() == 43);
				}
			}
		}

		WHEN("Defining an unary function with nan variable")
		{
			calculator.DeclareVar("var1");
			CHECK(std::isnan(calculator.GetValue("var1").value()));
			CHECK(calculator.DefineUnaryFn("fn1", "var1"));

			THEN("Function value will be nan")
			{
				CHECK(std::isnan(calculator.GetValue("fn1").value()));
			}

			AND_WHEN("Redefining this function with another variable")
			{
				CHECK(calculator.DeclareVar("var2"));

				THEN("It can't be done")
				{
					CHECK(!calculator.DefineUnaryFn("fn1", "var1"));
				}
			}

			WHEN("Assigning the variable a value")
			{
				calculator.DefineVarWithNumber("var1", "42");
				CHECK(calculator.GetValue("var1").value() == 42);

				THEN("Function will also have value")
				{
					CHECK(calculator.GetValue("fn1").value() == 42);
				}

				AND_WHEN("Changing variable's value")
				{
					calculator.DefineVarWithNumber("var1", "43");
					CHECK(calculator.GetValue("var1").value() == 43);

					THEN("Function's value changes")
					{
						CHECK(calculator.GetValue("fn1").value() == 43);
					}
				}
			}
		}

		WHEN("Defining a binary function with at least one nan variable and that does addition")
		{
			calculator.DeclareVar("var1");
			calculator.DefineVarWithNumber("var2", "42");
			CHECK(std::isnan(calculator.GetValue("var1").value()));
			CHECK(calculator.GetValue("var2").value() == 42);
			CHECK(calculator.DefineBinaryFn("fn1", "var1", "var2", [](const double first, const double second) {
				return first + second;
			}));

			THEN("Function value will be nan")
			{
				CHECK(std::isnan(calculator.GetValue("fn1").value()));
			}

			AND_WHEN("Redefining this function with another variable")
			{
				CHECK(calculator.DeclareVar("var3"));

				THEN("It can't be done")
				{
					CHECK(!calculator.DefineBinaryFn("fn1", "var3", "var2", [](const double first, const double second) {
						return first + second;
					}));
				}
			}

			WHEN("Assigning the nan variable a value")
			{
				calculator.DefineVarWithNumber("var1", "10");
				CHECK(calculator.GetValue("var1").value() == 10);

				THEN("Function will also have value")
				{
					CHECK(calculator.GetValue("fn1").value() == 52);
				}

				AND_WHEN("Changing variable's value")
				{
					calculator.DefineVarWithNumber("var2", "43");
					CHECK(calculator.GetValue("var2").value() == 43);

					THEN("Function's value changes")
					{
						CHECK(calculator.GetValue("fn1").value() == 53);
					}
				}
			}
		}

		WHEN("Defining a binary function that does subtraction")
		{
			calculator.DefineVarWithNumber("var1", "20");
			calculator.DefineVarWithNumber("var2", "5");
			CHECK(calculator.GetValue("var1").value() == 20);
			CHECK(calculator.GetValue("var2").value() == 5);
			CHECK(calculator.DefineBinaryFn("fn1", "var1", "var2", [](const double first, const double second) {
				return first - second;
			}));

			THEN("Function does subtraction correctly")
			{
				CHECK(calculator.GetValue("fn1").value() == 15);
			}
		}

		WHEN("Defining a binary function that does multiplication")
		{
			calculator.DefineVarWithNumber("var1", "20");
			calculator.DefineVarWithNumber("var2", "5");
			CHECK(calculator.GetValue("var1").value() == 20);
			CHECK(calculator.GetValue("var2").value() == 5);
			CHECK(calculator.DefineBinaryFn("fn1", "var1", "var2", [](const double first, const double second) {
				return first * second;
			}));

			THEN("Function does multiplication correctly")
			{
				CHECK(calculator.GetValue("fn1").value() == 100);
			}
		}

		WHEN("Defining a binary function that does division")
		{
			calculator.DefineVarWithNumber("var1", "20");
			calculator.DefineVarWithNumber("var2", "5");
			CHECK(calculator.GetValue("var1").value() == 20);
			CHECK(calculator.GetValue("var2").value() == 5);
			CHECK(calculator.DefineBinaryFn("fn1", "var1", "var2", [](const double first, const double second) {
				return second == 0 ? std::numeric_limits<double>::quiet_NaN() : first / second;
			}));

			THEN("Function does division correctly")
			{
				CHECK(calculator.GetValue("fn1").value() == 4);
			}

			AND_WHEN("Second variable is zero")
			{
				calculator.DefineVarWithNumber("var2", "0");
				CHECK(calculator.GetValue("var2").value() == 0);

				THEN("Function's value will be nan")
				{
					CHECK(std::isnan(calculator.GetValue("fn1").value()));
				}
			}
		}
	}
}

SCENARIO("Testing calculator app")
{
	GIVEN("Calculator and app")
	{
		std::istringstream iss;
		std::ostringstream oss;

		CCalculatorEngine calculator;
		CCalculatorApp app(calculator, iss, oss);
	}
}