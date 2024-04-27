#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../MyIterator.h"
#include "../MyString.h"
#include <sstream>
#include <utility>

SCENARIO("Testing string constructors")
{
	WHEN("Creating string with default constructor")
	{
		MyString str;

		THEN("It will have zero size")
		{
			CHECK(str == "");
			CHECK(str.GetLength() == 0u);
		}
	}

	WHEN("Creating string from char array")
	{
		const char* cStr = "Hello";
		MyString str(cStr);

		THEN("It will have data and size of char array")
		{
			CHECK(str == "Hello");
			CHECK(str.GetLength() == 5u);
		}
	}

	WHEN("Creating string from std::string")
	{
		std::string stlStr = "Hello";
		MyString str(stlStr);

		THEN("It will have data and size of std::string")
		{
			CHECK(str == stlStr);
			CHECK(str.GetLength() == stlStr.size());
		}
	}

	WHEN("Creating string with copy constructor from another string")
	{
		MyString oldStr("Hello");
		MyString newStr(oldStr);

		THEN("It will have data and size of other string")
		{
			CHECK(newStr == oldStr);
			CHECK(newStr.GetLength() == oldStr.GetLength());

			AND_THEN("Old string will remain intact")
			{
				CHECK(oldStr == "Hello");
				CHECK(oldStr.GetLength() == 5u);
			}
		}
	}

	WHEN("Creating string with move constructor from another string")
	{
		MyString oldStr("Hello");
		MyString newStr(std::move(oldStr));

		THEN("It will have data and size of other string")
		{
			CHECK(newStr == "Hello");
			CHECK(newStr.GetLength() == 5u);

			AND_THEN("Old string will be empty")
			{
				CHECK(oldStr == "");
				CHECK(oldStr.GetLength() == 0);
			}
		}
	}
}

SCENARIO("Testing SubString function")
{
	GIVEN("A string")
	{
		MyString str("The quick brown fox jumps over the lazy dog");

		WHEN("Taking substring with one argument (start position)")
		{
			MyString substr;
			substr = str.SubString(16);

			THEN("New string will be from provided position till the end")
			{
				CHECK(substr == "fox jumps over the lazy dog");
			}
		}

		WHEN("Taking substring with two arguments (start position and length)")
		{
			MyString substr;
			substr = str.SubString(16, 9);

			THEN("New string will be from provided position and will have provided length")
			{
				CHECK(substr == "fox jumps");
			}
		}

		WHEN("Taking substring, but provided position is greater than string length")
		{
			MyString substr;

			THEN("Exception will be thrown")
			{
				CHECK_THROWS(substr = str.SubString(44));
			}

			AND_WHEN("Position is the last character in string")
			{
				substr = str.SubString(42);

				THEN("New string will be one last character")
				{
					CHECK(substr == "g");
				}
			}
		}
	}
}

SCENARIO("Testing Clear function")
{
	GIVEN("A string")
	{
		MyString str("The quick brown fox jumps over the lazy dog");

		WHEN("Clearing string")
		{
			str.Clear();

			THEN("String will be empty")
			{
				CHECK(str == "");
			}
		}
	}
}

SCENARIO("Testing copy assignment and move assignment operators")
{
	GIVEN("A string")
	{
		MyString orig("Hello");

		WHEN("Creating new string and then copy assigning to it original string's value")
		{
			MyString newStr;
			newStr = orig;

			THEN("Strings will be equal")
			{
				CHECK(orig == newStr);
				CHECK(orig == "Hello");
			}
		}

		WHEN("Creating new string and then move assigning to it original string's value")
		{
			MyString newStr;
			newStr = std::move(orig);

			THEN("New string will have data of original string")
			{
				CHECK(newStr == "Hello");

				AND_THEN("Original string will be empty")
				{
					CHECK(orig == "");
				}
			}
		}
	}
}

SCENARIO("Testing plus operator")
{
	GIVEN("Some strings")
	{
		MyString str1("Hello");
		MyString str2("World");
		std::string stlStr("std::string");
		const char* cStr = "C-style string";

		MyString result;

		WHEN("Adding two my strings together")
		{
			result = str1 + str2;

			THEN("Strings will be concatenated")
			{
				CHECK(result == "HelloWorld");
			}
		}

		WHEN("Adding my string and std::string together")
		{
			result = str1 + stlStr;

			THEN("Strings will be concatenated")
			{
				CHECK(result == "Hellostd::string");
			}

			AND_WHEN("Adding std::string and my string together")
			{
				result = stlStr + str1;

				THEN("Strings will be concatenated")
				{
					CHECK(result == "std::stringHello");
				}
			}
		}

		WHEN("Adding my string and C-style string together")
		{
			result = str1 + cStr;

			THEN("Strings will be concatenated")
			{
				CHECK(result == "HelloC-style string");
			}

			AND_WHEN("Adding C-style string and my string together")
			{
				result = cStr + str1;

				THEN("Strings will be concatenated")
				{
					CHECK(result == "C-style stringHello");
				}
			}
		}
	}
}

SCENARIO("Testing addition assignment operator")
{
	GIVEN("Two strings")
	{
		MyString str1("Hello");
		MyString str2(" World");

		CHECK(str1.GetCapacity() == 5u);

		WHEN("Adding second string to first")
		{
			str1 += str2;

			THEN("Two strings get concatenated, reallocation of memory happens")
			{
				CHECK(str1 == "Hello World");
				CHECK(str1.GetCapacity() == 22u);

				AND_WHEN("Adding second string to first one more time")
				{
					str1 += str2;

					THEN("Two strings get concatenated without memory reallocation")
					{
						CHECK(str1 == "Hello World World");
						CHECK(str1.GetCapacity() == 22u);
					}
				}
			}
		}
	}
}

SCENARIO("Testing index operator")
{
	GIVEN("A string")
	{
		MyString str("Hello");

		WHEN("Index is within the range of string")
		{
			THEN("Char is returned")
			{
				CHECK(str[4] == 'o');
			}

			AND_WHEN("Trying to change the char")
			{
				str[4] = '!';

				THEN("It changes because string wasn't const")
				{
					CHECK(str == "Hell!");
				}
			}
		}

		WHEN("Index is outside of the string range")
		{
			THEN("Exception is thrown")
			{
				CHECK_THROWS(str[5]);
			}
		}
	}

	GIVEN("A const string")
	{
		const MyString str("Hello");

		WHEN("Trying to change single char in string by index")
		{
			THEN("Project won't compile")
			{
				// str[4] = 'a';
			}
		}
	}
}

SCENARIO("Testing relational operators")
{
	GIVEN("Two same string and one different")
	{
		MyString str1("Hello");
		MyString str2("Hello");
		MyString str3("Hellp");

		WHEN("Comparing strings")
		{
			THEN("Comparing works")
			{
				CHECK(str1 == str2);
				CHECK_FALSE(str1 == str3);

				CHECK_FALSE(str1 != str2);
				CHECK(str1 != str3);

				CHECK(str3 > str1);
				CHECK(str3 >= str1);
				CHECK(str1 >= str2);

				CHECK(str1 < str3);
				CHECK(str1 <= str3);
				CHECK(str1 <= str2);
			}
		}
	}
}

SCENARIO("Testing input and output operators")
{
	GIVEN("Default string")
	{
		MyString str;
		std::istringstream iss;
		// std::ostringstream oss;

		WHEN("Reading input")
		{
			iss.str("Hello, world");
			iss >> str;

			THEN("Input is read")
			{
				CHECK(str == "Hello, world");
			}
		}
	}
}

SCENARIO("Testing non-const iterator")
{
	GIVEN("Non-const string and iterator")
	{
		MyString str("0123456789");
		auto it(str.begin());

		WHEN("Incrementing iterator")
		{
			it++;
			++it;

			THEN("It works")
			{
				CHECK(*it == '2');
			}

			AND_WHEN("Decrementing iterator")
			{
				it--;
				--it;

				THEN("It works")
				{
					CHECK(*it == '0');
				}
			}
		}

		WHEN("Adding number to iterator")
		{
			it = it + 5;

			THEN("It works")
			{
				CHECK(*it == '5');
			}

			AND_WHEN("Adding iterator to number")
			{
				it = 3 + it;

				THEN("It works")
				{
					CHECK(*it == '8');
				}

				AND_WHEN("Subtracting number from iterator")
				{
					it = it - 4;

					THEN("It works")
					{
						CHECK(*it == '4');
					}
				}
			}
		}

		WHEN("Subtracting one iterator from another")
		{
			auto end(str.end());

			THEN("It works")
			{
				CHECK(end - it == str.GetLength());
			}
		}

		WHEN("Addition assigning number to iterator")
		{
			it += 3;

			THEN("It works")
			{
				CHECK(*it == '3');
			}

			AND_WHEN("Subtraction assignment number to iterator")
			{
				it -= 2;

				THEN("It works")
				{
					CHECK(*it == '1');
				}
			}
		}

		WHEN("Taking value by index relative to iterator")
		{
			THEN("It works")
			{
				CHECK(it[5] == '5');
			}
		}

		WHEN("Comparing iterators")
		{
			auto begin(str.begin());
			auto end(str.end());

			THEN("Comparing works")
			{
				CHECK(it == begin);
				CHECK_FALSE(it == end);

				CHECK_FALSE(it != begin);
				CHECK(it != end);

				CHECK(end > it);
				CHECK(end >= it);
				CHECK(it >= begin);

				CHECK(it < end);
				CHECK(it <= end);
				CHECK(it <= begin);
			}
		}

		WHEN("Changing string value through iterator")
		{
			*it = 'a';
			it[5] = 'b';

			THEN("Value is changed")
			{
				CHECK(str == "a1234b6789");
			}
		}
	}
}

SCENARIO("Testing const iterator")
{
	GIVEN("Const string and iterator")
	{
		const MyString str("0123456789");
		auto it(str.begin());

		it++;
		CHECK(*it == '1');

		++it;
		CHECK(*it == '2');

		it--;
		CHECK(*it == '1');

		--it;
		CHECK(*it == '0');

		it = it + 5;
		CHECK(*it == '5');

		it = 3 + it;
		CHECK(*it == '8');

		it = it - 4;
		CHECK(*it == '4');

		it += 3;
		CHECK(*it == '7');

		it -= 7;
		CHECK(*it == '0');

		// *it = 'a';
		// it[2] = 'b';
	}
}

SCENARIO("Testing begin/end and rbegin/rend functions and range-based for loop")
{
	GIVEN("A string")
	{
		MyString str("Able was I ere I saw Elba");
		std::ostringstream oss;

		WHEN("Iterating from begin to end")
		{
			auto it(str.begin());
			auto end(str.end());

			while (it != end)
			{
				oss << *it;
				++it;
			}

			THEN("String is printed in forward order")
			{
				CHECK(oss.str() == "Able was I ere I saw Elba");
			}
		}

		WHEN("Iterating from rbegin to rend")
		{
			auto it(str.rbegin());
			auto end(str.rend());

			while (it != end)
			{
				oss << *it;
				++it;
			}

			THEN("String is printed in reverse order")
			{
				CHECK(oss.str() == "ablE was I ere I saw elbA");
			}
		}

		WHEN("Iterating over string with range-based for loop")
		{
			for (auto ch : str)
			{
				oss << ch;
			}

			THEN("String is printed correctly")
			{
				CHECK(oss.str() == "Able was I ere I saw Elba");
			}
		}
	}
}