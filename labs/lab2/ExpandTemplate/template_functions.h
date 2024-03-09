#pragma once

#include <string>
#include <map>
#include <array>
#include <vector>

constexpr int MAX_CHARS = 256;
constexpr int LINK_TO_ROOT = -1;

using ParamsMap = std::map<std::string, std::string>;

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	ParamsMap params;
};

struct Vertex
{
	std::array<int, MAX_CHARS> next;
	std::array<int, MAX_CHARS> autoMove;
	int parent;
	char ch;
	bool isTerminal;
	int suffLink;
};

using Trie = std::vector<Vertex>;

void CopyFileWithReplacements(const Args& args);
std::string ExpandTemplate(const std::string& tpl, Trie& trie, const ParamsMap& params);
Trie InitTrie(const ParamsMap& params);