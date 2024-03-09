#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../template_functions.h"

TEST_CASE("Testing")
{
	{
		const std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		ParamsMap params;
		params["%USER_NAME%"] = "Ivan Petrov";
		params["{WEEK_DAY}"] = "Friday";
		Trie trie = InitTrie(params);

		CHECK(ExpandTemplate(tpl, trie, params) == "Hello, Ivan Petrov. Today is Friday.");
	}

	{
		const std::string tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
		ParamsMap params;
		params["%USER_NAME%"] = "Super %USER_NAME% {WEEK_DAY}";
		params["{WEEK_DAY}"] = "Friday. {WEEK_DAY}";
		Trie trie = InitTrie(params);

		CHECK(ExpandTemplate(tpl, trie, params) == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
	}

	{
		const std::string tpl = "-AABBCCCCCABC+";
		ParamsMap params;
		params["A"] = "[a]";
		params["AA"] = "[aa]";
		params["B"] = "[b]";
		params["BB"] = "[bb]";
		params["C"] = "[c]";
		params["CC"] = "[cc]";
		Trie trie = InitTrie(params);

		CHECK(ExpandTemplate(tpl, trie, params) == "-[aa][bb][cc][cc][c][a][b][c]+");
	}

	{
		const std::string tpl = "aabbcc";
		ParamsMap params;
		params["a"] = " a ";
		params["aa"] = " aa ";
		params["b"] = " b ";
		params["bb"] = " bb ";
		params["c"] = " c ";
		params["cc"] = " cc ";
		Trie trie = InitTrie(params);

		CHECK(ExpandTemplate(tpl, trie, params) == " aa  bb  cc ");
	}

	{
		const std::string tpl = "mama";
		ParamsMap params;
		params["m"] = "a";
		params["a"] = "m";
		params["ma"] = "mama";
		Trie trie = InitTrie(params);

		CHECK(ExpandTemplate(tpl, trie, params) == "mamamama");
	}

	{
		const std::string tpl = "mama";
		ParamsMap params;
		params["ma"] = "mama";
		params["mama"] = "mother";
		Trie trie = InitTrie(params);

		CHECK(ExpandTemplate(tpl, trie, params) == "mother");
	}

	{
		const std::string tpl = "mama";
		ParamsMap params;
		params[""] = "";
		params[""] = "";
		Trie trie = InitTrie(params);

		CHECK(ExpandTemplate(tpl, trie, params) == "mama");
	}
}