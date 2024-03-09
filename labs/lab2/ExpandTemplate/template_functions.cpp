#include "template_functions.h"
#include <fstream>
#include <algorithm>

namespace
{

Vertex MakeNewVertex(int par, char c)
{
	Vertex v;

	v.next.fill(LINK_TO_ROOT);
	v.autoMove.fill(LINK_TO_ROOT);
	v.parent = par;
	v.ch = c;
	v.isTerminal = false;
	v.suffLink = LINK_TO_ROOT;

	return v;
}

void AddStringToTrie(Trie& trie, const std::string& str)
{
	int vertexPos = 0;

	for (char ch : str)
	{
		if (trie[vertexPos].next[ch] == LINK_TO_ROOT)
		{
			Vertex v = MakeNewVertex(vertexPos, ch);
			trie[vertexPos].next[ch] = trie.size();
			trie.push_back(v);
		}

		vertexPos = trie[vertexPos].next[ch];
	}

	trie[vertexPos].isTerminal = true;
}

int GetAutoMove(Trie& trie, size_t vertexPos, char ch);

int GetSuffixLink(Trie& trie, size_t vertexPos)
{
	if (trie[vertexPos].suffLink == LINK_TO_ROOT)
	{
		if (vertexPos == 0 || trie[vertexPos].parent == 0)
		{
			trie[vertexPos].suffLink = 0;
		}
		else
		{
			trie[vertexPos].suffLink = GetAutoMove(trie, GetSuffixLink(trie, trie[vertexPos].parent), trie[vertexPos].ch);
		}
	}

	return trie[vertexPos].suffLink;
}

int GetAutoMove(Trie& trie, size_t vertexPos, char ch)
{
	if (trie[vertexPos].autoMove[ch] == LINK_TO_ROOT)
	{
		if (trie[vertexPos].next[ch] != LINK_TO_ROOT)
		{
			trie[vertexPos].autoMove[ch] = trie[vertexPos].next[ch];
		}
		else if (vertexPos == 0)
		{
			trie[vertexPos].autoMove[ch] = 0;
		}
		else
		{
			trie[vertexPos].autoMove[ch] = GetAutoMove(trie, GetSuffixLink(trie, vertexPos), ch);
		}
	}

	return trie[vertexPos].autoMove[ch];
}

size_t CheckForLengthierWord(Trie& trie, size_t vertex, const std::string& tpl, size_t& pos)
{
	size_t newVertex = vertex;
	size_t currentVertex = vertex;
	bool isEnd = false;

	while (!isEnd)
	{
		if (trie[newVertex].isTerminal)
		{
			vertex = newVertex;
		}

		pos++;
		if (pos >= tpl.length())
		{
			break;
		}

		currentVertex = newVertex;
		newVertex = GetAutoMove(trie, newVertex, tpl[pos]);

		isEnd = trie[newVertex].parent != currentVertex;
	}
	pos--;

	return vertex;
}

std::string GetWordFromTrie(const Trie& trie, size_t vertex)
{
	std::string word;
	word.reserve(trie.size());

	while (vertex != 0)
	{
		word += trie[vertex].ch;
		vertex = trie[vertex].parent;
	}

	std::reverse(word.begin(), word.end());

	return word;
}

std::string ExpandTemplate(const std::string& tpl, Trie& trie, const ParamsMap& params, size_t estimatedLength)
{
	if (params.empty())
	{
		return tpl;
	}

	std::string result;
	result.reserve(estimatedLength);

	size_t vertexPos = 0;
	size_t stringPos = 0;

	for (size_t i = 0; i < tpl.length(); ++i)
	{
		vertexPos = GetAutoMove(trie, vertexPos, tpl[i]);

		if (trie[vertexPos].isTerminal)
		{
			vertexPos = CheckForLengthierWord(trie, vertexPos, tpl, i);

			std::string key = GetWordFromTrie(trie, vertexPos);
			result += tpl.substr(stringPos, i - stringPos - key.size() + 1);
			stringPos = i + 1;
			result += params.find(key)->second;

			vertexPos = 0;
		}
	}
	result += tpl.substr(stringPos);

	return result;
}

} // namespace

void CopyFileWithReplacements(const Args& args)
{
	std::ifstream inputFile(args.inputFileName);
	std::ofstream outputFile(args.outputFileName);
	if (!inputFile.is_open() || !outputFile.is_open())
	{
		throw std::runtime_error("Couldn't open file");
	}

	Trie trie = InitTrie(args.params);

	std::string line;
	while (std::getline(inputFile, line))
	{
		std::string result = ExpandTemplate(line, trie, args.params);
		outputFile << result << "\n";
	}
}

std::string ExpandTemplate(const std::string& tpl, Trie& trie, const ParamsMap& params)
{
	size_t estimatedLength = tpl.length();

	for (auto it = params.begin(); it != params.end(); ++it)
	{
		estimatedLength += it->second.length();
	}

	return ExpandTemplate(tpl, trie, params, estimatedLength);
}

Trie InitTrie(const ParamsMap& params)
{
	Trie trie;

	trie.push_back(MakeNewVertex(/*parent*/ 0, /*char*/ '$'));

	for (const auto& keyValue : params)
	{
		AddStringToTrie(trie, keyValue.first);
	}

	return trie;
}