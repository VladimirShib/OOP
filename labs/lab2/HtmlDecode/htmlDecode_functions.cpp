#include "htmlDecode_functions.h"

void DecodeInput(std::istream& input, std::ostream& output)
{
	DecodeList decodeList = { { "&quot;", '\"' }, { "&apos;", '\'' }, { "&lt;", '<' }, { "&gt;", '>' }, { "&amp;", '&' } };
	std::string line;

	while (std::getline(input, line))
	{
		output << HtmlDecode(line, decodeList) << "\n";
	}
}

std::string HtmlDecode(const std::string& html, const DecodeList& decodeList)
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

		text += (ReplaceHtmlCodeWithCharacter(html.substr(foundPos, MAX_SUBSTR_LENGTH), foundPos, decodeList));
		pos = ++foundPos;
	}

	return text;
}

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