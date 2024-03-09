#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../dictionary_functions.h"
#include <sstream>

TEST_CASE("One meaning")
{
	Dictionary dictionary;
	AddToDictionary(dictionary, "cat", "kot");
	AddToDictionary(dictionary, "car", "automobil");
	AddToDictionary(dictionary, "pc", "computer");

	std::istringstream iss;
	std::ostringstream oss;
	std::string input;
	std::string output;
	bool changesWereMade = false;

	WHEN("Input `cat`, output should be `kot`")
	{
		input = "cat";
		ProcessUserInput(iss, oss, dictionary, input, changesWereMade);
		output = oss.str();
		CHECK(output == "kot\n\n");
	}

	WHEN("Input `car`, output should be `automobil`")
	{
		input = "car";
		ProcessUserInput(iss, oss, dictionary, input, changesWereMade);
		output = oss.str();
		CHECK(output == "automobil\n\n");
	}

	WHEN("Input `pc`, output should be `computer`")
	{
		input = "pc";
		ProcessUserInput(iss, oss, dictionary, input, changesWereMade);
		output = oss.str();
		CHECK(output == "computer\n\n");
	}

	WHEN("Input `red`, no translation")
	{
		input = "red";
		ProcessUserInput(iss, oss, dictionary, input, changesWereMade);
		output = oss.str();
		CHECK(output == "Unknown word \"red\". Enter translation or empty string to cancel.\nThe word \"red\" has been ignored.\n\n");
	}
}

TEST_CASE("Several meanings")
{
	Dictionary dictionary;
	AddToDictionary(dictionary, "cat", "kot");
	AddToDictionary(dictionary, "cat", "kotik");
	AddToDictionary(dictionary, "spring", "vesna");
	AddToDictionary(dictionary, "spring", "rodnik");
	AddToDictionary(dictionary, "spring", "istochnik");
	AddToDictionary(dictionary, "castle", "zamok");
	AddToDictionary(dictionary, "lock", "zamok");

	std::istringstream iss;
	std::ostringstream oss;
	std::string input;
	std::string output;
	bool changesWereMade = false;

	WHEN("Input `cat`, output should be `kot, kotik`")
	{
		input = "cat";
		ProcessUserInput(iss, oss, dictionary, input, changesWereMade);
		output = oss.str();
		CHECK(output == "kot, kotik\n\n");
	}

	WHEN("Input `spring`, output should be `vesna, rodnik, istochnik`")
	{
		input = "spring";
		ProcessUserInput(iss, oss, dictionary, input, changesWereMade);
		output = oss.str();
		CHECK(output == "vesna, rodnik, istochnik\n\n");
	}

	WHEN("Input `castle`, output should be `zamok`")
	{
		input = "castle";
		ProcessUserInput(iss, oss, dictionary, input, changesWereMade);
		output = oss.str();
		CHECK(output == "zamok\n\n");
	}

	WHEN("Input `lock`, output should be `zamok`")
	{
		input = "lock";
		ProcessUserInput(iss, oss, dictionary, input, changesWereMade);
		output = oss.str();
		CHECK(output == "zamok\n\n");
	}
}