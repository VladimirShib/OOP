#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <stdexcept>
#include <map>

using Dictionary = std::map<std::string, std::string>;

void RunDictionary(std::istream& input, std::ostream& output, const std::optional<std::string>& dictionaryFile);
void AddToDictionary(Dictionary& dictionary, const std::string& key, const std::string& value);
void ProcessUserInput(std::istream& input, std::ostream& output, Dictionary& dictionary,
	const std::string& userInput, bool& changesWereMade);