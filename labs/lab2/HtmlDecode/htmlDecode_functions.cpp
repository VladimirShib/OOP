#include "htmlDecode_functions.h"
#include <string>
#include <string_view>
#include <vector>
#include <utility>

namespace
{

constexpr size_t MAX_SUBSTR_LENGTH = 6;
using DecodeList = std::vector<std::pair<std::string, char>>;

char ReplaceHtmlCodeWithCharacter(const std::string_view& code, size_t& foundPos, const DecodeList& decodeList)
{
	char replacement = '&';

	for (size_t i = 0; i < decodeList.size(); ++i)
	{
		size_t findReplacement = code.find(decodeList[i].first);
		if (findReplacement == 0)
		{
			replacement = decodeList[i].second;
			foundPos += decodeList[i].first.size() - 1;
		}
	}

	return replacement;
}

std::string HtmlDecode(const std::string_view& html, const DecodeList& decodeList)
{
	std::string text;
	size_t pos = 0;

	while (pos < html.length())
	{
		size_t foundPos = html.find("&", pos);
		text.append(html, pos, foundPos - pos);

		if (foundPos == std::string::npos)
		{
			break;
		}

		text += ReplaceHtmlCodeWithCharacter(html.substr(foundPos, MAX_SUBSTR_LENGTH), foundPos, decodeList);
		pos = foundPos + 1;
	}

	return text;
}

} // namespace

void DecodeInput(std::istream& input, std::ostream& output)
{
	const DecodeList decodeList = { { "&quot;", '\"' }, { "&apos;", '\'' }, { "&lt;", '<' }, { "&gt;", '>' }, { "&amp;", '&' } };
	std::string line;

	while (std::getline(input, line))
	{
		output << HtmlDecode(line, decodeList) << "\n";
	}
}