#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../MyList.h"
#include <sstream>
#include <string>

SCENARIO("Testing constructors")
{
	WHEN("Creating lists with default constructor")
	{
		MyList<std::string> listOfStr;
		MyList<int> listOfInts;

		THEN("The size is zero")
		{
			CHECK(listOfStr.Empty());
			CHECK(listOfInts.Empty());
		}
	}

	WHEN("Creating lists with initializer list")
	{
		MyList<std::string> listOfStr = { "Hello", "World" };
		MyList<int> listOfInts = { 1, 2, 3 };

		THEN("The size equals to initializer list's size")
		{
			CHECK(listOfStr.Size() == 2);
			CHECK(listOfStr.Front() == "Hello");
			CHECK(listOfStr.Back() == "World");

			CHECK(listOfInts.Size() == 3);
			CHECK(listOfInts.Front() == 1);
			CHECK(listOfInts.Back() == 3);
		}
	}

	WHEN("Creating string list with copy constructor from another string list")
	{
		MyList<std::string> oldList = { "Hello", "World" };
		MyList<std::string> newList = oldList;

		THEN("New list will have size and data of old list, and old list will remain intact")
		{
			CHECK(newList.Size() == 2);
			CHECK(newList.Front() == "Hello");
			CHECK(newList.Back() == "World");
			CHECK(oldList.Size() == 2);
		}
	}

	WHEN("Creating string list with move constructor from another string list")
	{
		MyList<std::string> oldList = { "Hello", "World" };
		MyList<std::string> newList = std::move(oldList);

		THEN("Old list data will be moved to new list")
		{
			CHECK(newList.Size() == 2);
			CHECK(newList.Front() == "Hello");
			CHECK(newList.Back() == "World");
			CHECK(oldList.Empty());
		}
	}
}

SCENARIO("Testing `PushFront`, `Front` and `PopFront` methods")
{
	GIVEN("String list with one element in it")
	{
		MyList<std::string> list = { "First" };
		CHECK(list.Size() == 1);
		CHECK(list.Front() == "First");

		WHEN("Pushing element to front")
		{
			list.PushFront("Hello");

			THEN("New element takes place at the beginning of list")
			{
				CHECK(list.Front() == "Hello");
				CHECK(list.Size() == 2);
			}

			AND_WHEN("Popping front element")
			{
				list.PopFront();

				THEN("Inserted element is no longer in the list")
				{
					CHECK(list.Front() == "First");
					CHECK(list.Size() == 1);
				}

				AND_WHEN("Popping front element again")
				{
					list.PopFront();

					THEN("List becomes empty")
					{
						CHECK(list.Empty());
					}
				}
			}
		}
	}
}

SCENARIO("Testing `PushBack`, `Back` and `PopBack` methods")
{
	GIVEN("String list with one element in it")
	{
		MyList<std::string> list = { "First" };
		CHECK(list.Size() == 1);
		CHECK(list.Back() == "First");

		WHEN("Pushing element to back")
		{
			list.PushBack("Hello");

			THEN("New element takes place at the end of list")
			{
				CHECK(list.Back() == "Hello");
				CHECK(list.Size() == 2);
			}

			AND_WHEN("Popping back element")
			{
				list.PopBack();

				THEN("Inserted element is no longer in the list")
				{
					CHECK(list.Back() == "First");
					CHECK(list.Size() == 1);
				}

				AND_WHEN("Popping back element again")
				{
					list.PopBack();

					THEN("List becomes empty")
					{
						CHECK(list.Empty());
					}
				}
			}
		}
	}
}

SCENARIO("Testing `Clear` method")
{
	GIVEN("String list with some data")
	{
		MyList<std::string> list = { "one", "two", "three" };
		CHECK(list.Size() == 3);

		WHEN("Clearing list")
		{
			list.Clear();

			THEN("List becomes empty")
			{
				CHECK(list.Empty());
			}
		}
	}
}

SCENARIO("Testing copy assignment and move assignment operators")
{
	GIVEN("String list with some data")
	{
		MyList<std::string> oldList = { "one", "two", "three" };

		WHEN("Creating new string list and then copy assigning to it old list's data")
		{
			MyList<std::string> newList;
			newList = oldList;

			THEN("New list will have size and data of old list, and old list will remain intact")
			{
				CHECK(newList.Size() == 3);
				CHECK(newList.Front() == "one");
				CHECK(newList.Back() == "three");
				CHECK(oldList.Size() == 3);
			}
		}

		WHEN("Creating new string list and then move assigning to it old list's data")
		{
			MyList<std::string> newList;
			newList = std::move(oldList);

			THEN("Old list data will be moved to new list")
			{
				CHECK(newList.Size() == 3);
				CHECK(newList.Front() == "one");
				CHECK(newList.Back() == "three");
				CHECK(oldList.Empty());
			}
		}

		WHEN("Copying list to itself")
		{
			oldList = oldList;

			THEN("Nothing bad happens")
			{
				CHECK(oldList.Size() == 3);
				CHECK(oldList.Front() == "one");
				CHECK(oldList.Back() == "three");
			}
		}

		WHEN("Moving list to itself")
		{
			oldList = std::move(oldList);

			THEN("Nothing bad happens")
			{
				CHECK(oldList.Size() == 3);
				CHECK(oldList.Front() == "one");
				CHECK(oldList.Back() == "three");
			}
		}
	}
}

SCENARIO("Testing iterators constness while dereferencing")
{
	GIVEN("Const and non-const string list")
	{
		MyList<std::string> list = { "one", "two", "three", "four", "five" };
		const MyList<std::string> constList = { "one", "two", "three", "four", "five" };

		WHEN("Taking begin iterator and dereferencing it")
		{
			auto it = list.begin();
			auto constIt = constList.begin();

			THEN("It prints stored string")
			{
				CHECK(*it == "one");
				CHECK(*constIt == "one");
			}

			AND_WHEN("Changing value")
			{
				*it = "new string";
				// *constIt = "new const string"; // can't change string with const iterator

				THEN("Only non-const iterator allows to change stored string")
				{
					CHECK(*it == "new string");
				}
			}
		}

		WHEN("Taking end iterator and dereferencing it")
		{
			auto it = list.end();

			THEN("Exception is thrown (because end iterator points to past-the-last element)")
			{
				CHECK_THROWS(*it);
			}
		}
	}
}

SCENARIO("Testing iterator incrementing and decrementing")
{
	GIVEN("String list and iterator")
	{
		MyList<std::string> listOfStr = { "one", "two", "three", "four", "five" };
		MyList<int> listOfInts = { 1, 2, 3 };
		auto it = listOfStr.begin();
		auto end = listOfInts.end();

		WHEN("Incrementing begin iterator")
		{
			it++;
			++it;

			THEN("It works")
			{
				CHECK(*it == "three");
			}

			AND_WHEN("Decrementing begin iterator")
			{
				it--;
				--it;

				THEN("It works")
				{
					CHECK(*it == "one");
				}
			}
		}

		WHEN("Decrementing end iterator")
		{
			--end;

			THEN("It works")
			{
				CHECK(*end == 3);
			}
		}
	}
}

SCENARIO("Testing begin/end and rbegin/rend methods and range-based for loop")
{
	GIVEN("String list")
	{
		MyList<std::string> list = { "One", "Two", "Three", "Four", "Five" };
		std::ostringstream oss;

		WHEN("Iterating from begin to end")
		{
			auto it = list.begin();
			auto end = list.end();

			while (it != end)
			{
				oss << *it;
				++it;
			}

			THEN("Strings are printed in forward order")
			{
				CHECK(oss.str() == "OneTwoThreeFourFive");
			}
		}

		WHEN("Iterating from rbegin to rend")
		{
			auto it = list.rbegin();
			auto end = list.rend();

			while (it != end)
			{
				oss << *it;
				++it;
			}

			THEN("Strings are printed in reverse order")
			{
				CHECK(oss.str() == "FiveFourThreeTwoOne");
			}
		}

		WHEN("Iterating over list with range-based for loop")
		{
			for (const auto& el : list)
			{
				oss << el;
			}

			THEN("Strings are printed correctly")
			{
				CHECK(oss.str() == "OneTwoThreeFourFive");
			}
		}
	}
}

SCENARIO("Testing `Insert` method")
{
	GIVEN("String list and iterator")
	{
		MyList<std::string> list = { "one, ", "two, ", "three" };
		auto it = list.begin();
		std::ostringstream oss;

		WHEN("Inserting element to the beginning of list")
		{
			it = list.Insert(it, "half, ");
			for (const auto& el : list)
			{
				oss << el;
			}

			THEN("New element takes place at the beginning of list and iterator points to it")
			{
				CHECK(oss.str() == "half, one, two, three");
				CHECK(*it == "half, ");
				CHECK(list.Size() == 4);
			}
		}

		WHEN("Inserting element to the middle")
		{
			++it;
			it = list.Insert(it, "one and a half, ");
			for (const auto& el : list)
			{
				oss << el;
			}

			THEN("New element takes place between first and second elements and iterator points to it")
			{
				CHECK(oss.str() == "one, one and a half, two, three");
				CHECK(*it == "one and a half, ");
				CHECK(list.Size() == 4);
			}
		}
	}
}

SCENARIO("Testing `Erase` method")
{
	GIVEN("String list and iterator")
	{
		MyList<std::string> list = { "one, ", "two, ", "three" };
		auto it = list.begin();
		std::ostringstream oss;

		WHEN("Erasing first element")
		{
			it = list.Erase(it);
			for (const auto& el : list)
			{
				oss << el;
			}

			THEN("First element gets erased, iterator to second element (which is now first) is returned")
			{
				CHECK(oss.str() == "two, three");
				CHECK(*it == "two, ");
				CHECK(list.Size() == 2);
			}
		}

		WHEN("Erasing last element")
		{
			++it;
			++it;
			it = list.Erase(it);
			for (const auto& el : list)
			{
				oss << el;
			}

			THEN("Last element gets erased, iterator to past-the-last element is returned")
			{
				CHECK(oss.str() == "one, two, ");
				CHECK_THROWS(*it);
				CHECK(list.Size() == 2);
			}
		}

		WHEN("Erasing middle element")
		{
			++it;
			it = list.Erase(it);
			for (const auto& el : list)
			{
				oss << el;
			}

			THEN("Middle element gets erased, iterator to next element is returned")
			{
				CHECK(oss.str() == "one, three");
				CHECK(*it == "three");
				CHECK(list.Size() == 2);
			}
		}

		WHEN("Erasing single element in list")
		{
			list.PopBack();
			list.PopBack();
			CHECK(list.Size() == 1);

			it = list.Erase(it);

			THEN("List becomes empty")
			{
				CHECK(list.Empty());
				CHECK_THROWS(*it);
			}
		}
	}
}