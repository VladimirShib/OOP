#include "dictionary_functions.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>

namespace
{

const std::string DEFAULT_DICTIONARY_PATH = "../../Dictionary/dictionary.txt";

void FillDictionaryFromFile(Dictionary& dictionary, const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Couldn't open file \"" + fileName + "\"");
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);

		std::string key;
		iss >> key;
		std::string value;
		iss >> value;

		AddToDictionary(dictionary, key, value);
		AddToDictionary(dictionary, value, key);

		while (iss >> value)
		{
			if (dictionary[key].find(value) == std::string::npos)
			{
				dictionary[key].push_back(',');
				dictionary[key] += (" " + value);
			}
			AddToDictionary(dictionary, value, key);
		}
	}
}

void ToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c) { return std::tolower(c); });
}

bool ProcessNewWord(std::istream& input, std::ostream& output, Dictionary& dictionary, const std::string& word)
{
	std::string translation;
	std::getline(input, translation);

	if (translation.empty())
	{
		output << "The word \"" + word + "\" has been ignored.\n\n";
		return false;
	}

	ToLower(translation);
	AddToDictionary(dictionary, word, translation);
	AddToDictionary(dictionary, translation, word);

	output << "\nThe word \"" + word + "\" has been saved to dictionary as \"" + translation + "\".\n\n";

	return true;
}

void SaveChangesToDictionary(const std::string& fileName, const Dictionary& dictionary)
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		throw std::runtime_error("Couldn't open file \"" + fileName + "\"");
	}

	std::string str;
	for (auto& pair : dictionary)
	{
		file << pair.first;
		std::istringstream iss(pair.second);
		while (iss >> str)
		{
			if (str.back() == ',')
			{
				str = str.substr(0, str.length() - 1);
			}
			file << " " << str;
		}
		file << "\n";
	}
}

void ProcessDialogEnding(std::istream& input, std::ostream& output, const Dictionary& dictionary,
	const std::string& fileName, const bool changesWereMade)
{
	if (!changesWereMade)
	{
		output << "See you later.\n";
	}
	else
	{
		output << "Changes have been made to the dictionary. Save them? Enter 'Y' or 'N'.\n\n";

		std::string answer;
		do
		{
			std::getline(input, answer);
			ToLower(answer);
		} while (answer != "y" && answer != "n");

		if (answer == "y")
		{
			SaveChangesToDictionary(fileName, dictionary);
			output << "Changes saved. See you later.\n";
		}
		else
		{
			output << "See you later.\n";
		}
	}
}

} // namespace

void RunDictionary(std::istream& input, std::ostream& output, const std::optional<std::string>& dictionaryFile)
{
	Dictionary dictionary;
	if (dictionaryFile.has_value())
	{
		FillDictionaryFromFile(dictionary, dictionaryFile.value());
	}

	const std::string END_CHAT_COMMAND = "...";
	std::string userInput;
	bool changesWereMade = false;

	output << "Translator 3000.\n\n";
	do
	{
		std::getline(input, userInput);
		if (userInput != END_CHAT_COMMAND)
		{
			ToLower(userInput);
			ProcessUserInput(input, output, dictionary, userInput, changesWereMade);
		}
	} while (userInput != END_CHAT_COMMAND);

	ProcessDialogEnding(input, output, dictionary,
		dictionaryFile.has_value() ? dictionaryFile.value() : DEFAULT_DICTIONARY_PATH, changesWereMade);
}

void AddToDictionary(Dictionary& dictionary, const std::string& key, const std::string& value)
{
	if (dictionary.find(key) == dictionary.end())
	{
		dictionary[key] = value;
	}
	else
	{
		if (dictionary[key].find(value) == std::string::npos)
		{
			dictionary[key].push_back(',');
			dictionary[key] += (" " + value);
		}
	}
}

void ProcessUserInput(std::istream& input, std::ostream& output, Dictionary& dictionary,
	const std::string& userInput, bool& changesWereMade)
{
	auto it = dictionary.find(userInput);
	if (it != dictionary.end())
	{
		output << it->second << "\n\n";
		return;
	}
	else
	{
		output << "Unknown word \"" + userInput + "\". Enter translation or empty string to cancel.\n";
	}

	if (ProcessNewWord(input, output, dictionary, userInput))
	{
		changesWereMade = true;
	}
}