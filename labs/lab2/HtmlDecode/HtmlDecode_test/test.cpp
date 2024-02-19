#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../htmlDecode_functions.h"

TEST_CASE("DecodeInput(std::istream&, std::ostream&)")
{
	SECTION("Empty input")
	{
		std::string input;
		std::istringstream iss(input);

		std::ostringstream oss;
		DecodeInput(iss, oss);
		std::string output = oss.str();

		CHECK(output == input);
	}
	
	SECTION("One-line input")
	{
		std::string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		std::string expectedOutput = "Cat <says> \"Meow\". M&M's\n";
		std::istringstream iss(input);

		std::ostringstream oss;
		DecodeInput(iss, oss);
		std::string output = oss.str();

		CHECK(output == expectedOutput);
	}
	
	SECTION("Multiline input")
	{
		std::string input = "Twinkle twinkle &quot;little&quot; star\nHow &apos;I&apos; wonder what you are\nUp above the &lt;world&gt; so high\nLike a &amp;diamond&amp; in the sky";
		std::string expectedOutput = "Twinkle twinkle \"little\" star\nHow 'I' wonder what you are\nUp above the <world> so high\nLike a &diamond& in the sky\n";
		std::istringstream iss(input);

		std::ostringstream oss;
		DecodeInput(iss, oss);
		std::string output = oss.str();

		CHECK(output == expectedOutput);
	}

	SECTION("Lots of symbols")
	{
		std::string input = "&lt;&amp;&amp;&amp;&gt;&quot;&apos;&apos;&quot;!@%&lt;*&gt;...&lt;|&gt;@&quot;&quot;&quot;&apos;&apos;&apos;";
		std::string expectedOutput = "<&&&>\"''\"!@%<*>...<|>@\"\"\"'''\n";
		std::istringstream iss(input);

		std::ostringstream oss;
		DecodeInput(iss, oss);
		std::string output = oss.str();

		CHECK(output == expectedOutput);
	}
	
	SECTION("Incomplete codes")
	{
		std::string input = "&amp&amp;&lt;&lt&gt;";
		std::string expectedOutput = "&amp&<&lt>\n";
		std::istringstream iss(input);

		std::ostringstream oss;
		DecodeInput(iss, oss);
		std::string output = oss.str();

		CHECK(output == expectedOutput);
	}
}