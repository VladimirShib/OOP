#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>

// Include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <tchar.h>

// TODO: reference additional headers your program requires here

#include <algorithm>
#include <cctype>
#include <map>
#include <optional>
#include <sstream>
#include <stdexcept>

// Function definitions

const std::string DEFAULT_DICTIONARY_PATH = "../../Dictionary/dictionary.txt";

using Dictionary = std::map<std::string, std::string>;

std::optional<std::string> ParseArguments(int argc, char* argv[]);
void RunDictionary(std::istream& input, std::ostream& output, const std::optional<std::string>& dictionaryFile);
void FillDictionaryFromFile(Dictionary& dictionary, const std::string& fileName);
void CheckAndAddToDictionary(Dictionary& dictionary, const std::string& key, const std::string& value);
void ProcessUserInput(std::istream& input, std::ostream& output, const Dictionary& dictionary,
	Dictionary& tempDictionary, const std::string& userInput);
void ProcessNewWord(std::istream& input, std::ostream& output, Dictionary& dictionary, const std::string& word);
void ProcessDialogEnding(std::istream& input, std::ostream& output, Dictionary& dictionary,
	const std::string& fileName);
void SaveChangesToDictionary(const std::string& fileName, Dictionary dictionary);
void ToLower(std::string& str);