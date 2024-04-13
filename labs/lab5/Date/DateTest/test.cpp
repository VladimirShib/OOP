#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../Date.h"
#include <sstream>

SCENARIO("Testing class constructor")
{
	GIVEN("Output stream")
	{
		std::ostringstream oss;

		WHEN("Creating class object with timestamp")
		{
			CDate date(2);
			oss << date;

			THEN("Date will be 03.01.1970")
			{
				CHECK(oss.str() == "03.01.1970");
			}
		}

		WHEN("Creating class object with date")
		{
			CDate date(7, Month::APRIL, 2024);
			oss << date;

			THEN("Date will be 07.04.2024")
			{
				CHECK(oss.str() == "07.04.2024");
			}
		}

		WHEN("Creating class object with no arguments")
		{
			CDate date;
			oss << date;

			THEN("Date will be 01.01.1970")
			{
				CHECK(oss.str() == "01.01.1970");
			}
		}
	}
}

SCENARIO("Testing GetDay function")
{
	WHEN("Creating class object with timestamp 30")
	{
		CDate date(30);

		THEN("It will be 31st day")
		{
			CHECK(date.GetDay() == 31u);
		}
	}

	WHEN("Creating class object with timestamp 31")
	{
		CDate date(31);

		THEN("It will be 1st day")
		{
			CHECK(date.GetDay() == 1u);
		}
	}

	WHEN("Creating class object with invalid date")
	{
		CDate date(-1);

		THEN("0 returns")
		{
			CHECK(date.GetDay() == 0);
		}
	}
}

SCENARIO("Testing GetMonth function")
{
	WHEN("Creating class object with timestamp 30")
	{
		CDate date(30);

		THEN("It will be january")
		{
			CHECK(date.GetMonth() == Month::JANUARY);
		}
	}

	WHEN("Creating class object with timestamp 31")
	{
		CDate date(31);

		THEN("It will be february")
		{
			CHECK(date.GetMonth() == Month::FEBRUARY);
		}
	}

	WHEN("Creating class object with invalid date")
	{
		CDate date(-1);

		THEN("No month returns")
		{
			CHECK(date.GetMonth() == Month::NO_MONTH);
		}
	}
}

SCENARIO("Testing GetYear function")
{
	WHEN("Creating class object with timestamp 30")
	{
		CDate date(364);

		THEN("It will be 1970")
		{
			CHECK(date.GetYear() == 1970u);
		}
	}

	WHEN("Creating class object with timestamp 31")
	{
		CDate date(365);

		THEN("It will be february")
		{
			CHECK(date.GetYear() == 1971u);
		}
	}

	WHEN("Creating class object with invalid date")
	{
		CDate date(-1);

		THEN("0 returns")
		{
			CHECK(date.GetYear() == 0);
		}
	}
}

SCENARIO("Testing GetWeekDay function")
{
	WHEN("Creating class object with timestamp 0")
	{
		CDate date(0);

		THEN("It will be thursday")
		{
			CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		}
	}

	WHEN("Creating class object with timestamp 4")
	{
		CDate date(4);

		THEN("It will be monday")
		{
			CHECK(date.GetWeekDay() == WeekDay::MONDAY);
		}
	}

	WHEN("Creating class object with invalid date")
	{
		CDate date(-1);

		THEN("No week day returns")
		{
			CHECK(date.GetWeekDay() == WeekDay::NO_WEEK_DAY);
		}
	}
}

SCENARIO("Testing IsValid function")
{
	WHEN("Creating class object with timestamp 0")
	{
		CDate date(0);

		THEN("Date is valid")
		{
			CHECK(date.IsValid());
		}
	}

	WHEN("Creating class object with max valid date")
	{
		CDate date(31, Month::DECEMBER, 9999);

		THEN("Date is valid")
		{
			CHECK(date.IsValid());
		}
	}

	WHEN("Creating class object with one day after max valid date")
	{
		CDate date(32, Month::DECEMBER, 9999);

		THEN("Date is invalid")
		{
			CHECK(!date.IsValid());
		}
	}

	WHEN("Creating class object with invalid date")
	{
		CDate date(-1);

		THEN("Date is invalid")
		{
			CHECK(!date.IsValid());
		}
	}
}

SCENARIO("Testing increment operator")
{
	GIVEN("Valid and invalid dates")
	{
		std::ostringstream oss;
		CDate validDate(5, Month::JANUARY, 1970);
		CDate invalidDate(-1);

		WHEN("Creating new date by assigning prefix incremented value of existing valid date")
		{
			CDate newDate = ++validDate;

			THEN("Both dates will be 06.01.1970")
			{
				oss << validDate;
				CHECK(oss.str() == "06.01.1970");
				oss.str("");

				oss << newDate;
				CHECK(oss.str() == "06.01.1970");
			}

			AND_WHEN("Incrementing new date further")
			{
				++newDate += 2;
				oss << newDate;

				THEN("Date will be 09.01.1970")
				{
					CHECK(oss.str() == "09.01.1970");
				}
			}
		}

		WHEN("Creating new date by assigning postfix incremented value of existing valid date")
		{
			CDate newDate = validDate++;

			THEN("New date will be assigned old value while valid date will be incremented")
			{
				oss << validDate;
				CHECK(oss.str() == "06.01.1970");
				oss.str("");

				oss << newDate;
				CHECK(oss.str() == "05.01.1970");

				/*AND_WHEN("Incrementing new date further")
				{
					newDate++ += 2;
					oss << newDate;

					THEN("Date will be 06.01.1970")
					{
						CHECK(oss.str() == "06.01.1970");
					}
				}*/
			}
		}

		WHEN("Prefix incrementing invalid date")
		{
			++invalidDate;
			oss << invalidDate;

			THEN("Date doesn't change")
			{
				CHECK(oss.str() == "INVALID");
			}
		}

		WHEN("Postfix incrementing invalid date")
		{
			invalidDate++;
			oss << invalidDate;

			THEN("Date doesn't change")
			{
				CHECK(oss.str() == "INVALID");
			}
		}
	}
}

SCENARIO("Testing decrement operator")
{
	GIVEN("Valid and invalid dates")
	{
		std::ostringstream oss;
		CDate validDate(5, Month::JANUARY, 1970);
		CDate invalidDate(2932897);

		WHEN("Creating new date by assigning prefix decremented value of existing valid date")
		{
			CDate newDate = --validDate;

			THEN("Both dates will be 04.01.1970")
			{
				oss << validDate;
				CHECK(oss.str() == "04.01.1970");
				oss.str("");

				oss << newDate;
				CHECK(oss.str() == "04.01.1970");
			}

			AND_WHEN("Decrementing new date further")
			{
				--newDate -= 2;
				oss << newDate;

				THEN("Date will be 01.01.1970")
				{
					CHECK(oss.str() == "01.01.1970");
				}
			}
		}

		WHEN("Creating new date by assigning postfix decremented value of existing valid date")
		{
			CDate newDate = validDate--;

			THEN("New date will be assigned old value while valid date will be decremented")
			{
				oss << validDate;
				CHECK(oss.str() == "04.01.1970");
				oss.str("");

				oss << newDate;
				CHECK(oss.str() == "05.01.1970");
			}
		}

		WHEN("Prefix decrementing invalid date")
		{
			--invalidDate;
			oss << invalidDate;

			THEN("Date doesn't change")
			{
				CHECK(oss.str() == "INVALID");
			}
		}

		WHEN("Postfix decrementing invalid date")
		{
			invalidDate--;
			oss << invalidDate;

			THEN("Date doesn't change")
			{
				CHECK(oss.str() == "INVALID");
			}
		}
	}
}

SCENARIO("Testing plus operator")
{
	GIVEN("Valid and invalid dates")
	{
		std::ostringstream oss;
		CDate validDate(5, Month::JANUARY, 1970);
		CDate invalidDate(-1);

		WHEN("Creating new date by adding 27 days to existing valid date")
		{
			CDate newDate = validDate + 27;

			THEN("New date will be 01.02.1970 and valid date won't change")
			{
				oss << validDate;
				CHECK(oss.str() == "05.01.1970");
				oss.str("");

				oss << newDate;
				CHECK(oss.str() == "01.02.1970");
			}
		}

		WHEN("Adding so many days to valid date so that it would become invalid")
		{
			validDate = validDate + 2932896;

			THEN("Valid date doesn't change")
			{
				oss << validDate;
				CHECK(oss.str() == "05.01.1970");
			}
		}

		WHEN("Creating new date by adding 1 day to existing invalid date")
		{
			CDate newDate = invalidDate + 1;

			THEN("New date will be invalid too")
			{
				oss << newDate;
				CHECK(oss.str() == "INVALID");
			}
		}
	}
}

SCENARIO("Testing minus operator")
{
	GIVEN("Valid and invalid dates")
	{
		std::ostringstream oss;
		CDate validDate(5, Month::JANUARY, 1971);
		CDate invalidDate(2932897);

		WHEN("Creating new date by subtracting 5 days from existing valid date")
		{
			CDate newDate = validDate - 5;

			THEN("New date will be 31.12.1970 and valid date won't change")
			{
				oss << validDate;
				CHECK(oss.str() == "05.01.1971");
				oss.str("");

				oss << newDate;
				CHECK(oss.str() == "31.12.1970");
			}
		}

		WHEN("Subtracting so many days from valid date so that it would become invalid")
		{
			validDate = validDate - 1000;

			THEN("Valid date doesn't change")
			{
				oss << validDate;
				CHECK(oss.str() == "05.01.1971");
			}
		}

		WHEN("Creating new date by subtracting 1 day from existing invalid date")
		{
			CDate newDate = invalidDate - 1;

			THEN("New date will be invalid too")
			{
				oss << newDate;
				CHECK(oss.str() == "INVALID");
			}
		}

		WHEN("Subtracting one date from another")
		{
			CDate date2(5, Month::JANUARY, 1970);
			int difference = validDate - date2;

			THEN("Difference will be 365 days")
			{
				CHECK(difference == 365);
			}

			AND_WHEN("Subtracting later date from earlier one")
			{
				difference = date2 - validDate;

				THEN("Difference will be negative")
				{
					CHECK(difference == -365);
				}
			}
		}

		WHEN("Subtracting leap-year date from non-leap-year date")
		{
			CDate leapYear(1, Month::JANUARY, 1972);
			CDate nonLeapYear(1, Month::JANUARY, 1973);
			int difference = nonLeapYear - leapYear;

			THEN("Difference should be 366 days")
			{
				CHECK(difference == 366);
			}
		}
	}
}

SCENARIO("Testing compound assignment operators")
{
	GIVEN("Valid and invalid dates")
	{
		std::ostringstream oss;
		CDate validDate(5, Month::JANUARY, 1971);
		CDate invalidDate1(-1);
		CDate invalidDate2(2932897);

		WHEN("Increasing valid date")
		{
			(validDate += 26) += 5;
			oss << validDate;

			THEN("Date will be 05.02.1971")
			{
				CHECK(oss.str() == "05.02.1971");
			}
		}

		WHEN("Increasing invalid date")
		{
			invalidDate1 += 31;
			oss << invalidDate1;

			THEN("Date still invalid")
			{
				CHECK(oss.str() == "INVALID");
			}
		}

		WHEN("Decreasing valid date")
		{
			(validDate -= 3) -= 2;
			oss << validDate;

			THEN("Date will be 31.12.1970")
			{
				CHECK(oss.str() == "31.12.1970");
			}
		}

		WHEN("Decreasing invalid date")
		{
			invalidDate2 -= 5;
			oss << invalidDate2;

			THEN("Date still invalid")
			{
				CHECK(oss.str() == "INVALID");
			}
		}
	}
}

SCENARIO("Testing output operator")
{
	GIVEN("Some date")
	{
		std::ostringstream oss;
		CDate date(1, Month::JANUARY, 1970);

		WHEN("Date is valid")
		{
			THEN("It will be printed in output")
			{
				oss << date;
				CHECK(oss.str() == "01.01.1970");
			}
		}

		WHEN("Date is invalid")
		{
			date--;

			THEN("INVALID will be printed")
			{
				oss << date;
				CHECK(oss.str() == "INVALID");
			}
		}
	}
}

SCENARIO("Testing input operator")
{
	GIVEN("Default date")
	{
		std::istringstream iss;
		std::ostringstream oss;
		CDate date;

		WHEN("Reading valid input without 0's")
		{
			iss.str("5.7.1970");
			iss >> date;
			oss << date;

			THEN("Date will be 05.07.1970")
			{
				CHECK(oss.str() == "05.07.1970");
				CHECK(!iss.fail());
			}
		}

		WHEN("Reading valid input with 0's")
		{
			iss.str("07.04.1970");
			iss >> date;
			oss << date;

			THEN("Date will be 07.04.1970")
			{
				CHECK(oss.str() == "07.04.1970");
				CHECK(!iss.fail());
			}
		}

		WHEN("Reading invalid input")
		{
			iss.str("1970-04-07");
			iss >> date;
			oss << date;

			THEN("Date won't change")
			{
				CHECK(oss.str() == "01.01.1970");
				CHECK(iss.fail());
			}
		}
	}
}

SCENARIO("Testing relational operators")
{
	GIVEN("Two same dates and one that differs")
	{
		CDate same1(5);
		CDate same2(5);
		CDate different(6);

		WHEN("Comparing dates")
		{
			THEN("Comparing works fine")
			{
				CHECK(same1 == same2);
				CHECK_FALSE(same1 == different);

				CHECK_FALSE(same1 != same2);
				CHECK(same1 != different);

				CHECK(different > same1);
				CHECK(different >= same1);
				CHECK(same1 >= same2);

				CHECK(same1 < different);
				CHECK(same1 < different);
				CHECK(same1 <= same2);
			}
		}
	}
}