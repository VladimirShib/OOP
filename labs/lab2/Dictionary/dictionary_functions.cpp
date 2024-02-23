#include "dictionary_functions.h"

std::optional<std::string> ParseArguments(int argc, char* argv[])
{
	if (argc != 2)
	{
		return std::nullopt;
	}

	return std::string(argv[1]);
}

void RunDictionary(std::istream& input, std::ostream& output, const std::optional<std::string>& dictionaryFile)
{
	Dictionary dictionary;
	if (dictionaryFile.has_value())
	{
		FillDictionaryFromFile(dictionary, dictionaryFile.value());
	}

	const std::string END_CHAT_COMMAND = "...";
	Dictionary tempDictionary;
	std::string userInput;

	output << "Translator 3000.\n\n";
	do
	{
		std::getline(input, userInput);
		if (userInput != END_CHAT_COMMAND)
		{
			ToLower(userInput);
			ProcessUserInput(input, output, dictionary, tempDictionary, userInput);
		}
	} while (userInput != END_CHAT_COMMAND);

	ProcessDialogEnding(input, output, tempDictionary,
		dictionaryFile.has_value() ? dictionaryFile.value() : DEFAULT_DICTIONARY_PATH);
}

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

		CheckAndAddToDictionary(dictionary, key, value);
		CheckAndAddToDictionary(dictionary, value, key);

		while (iss >> value)
		{
			if (dictionary[key].find(value) == std::string::npos)
			{
				dictionary[key].push_back(',');
				dictionary[key] += (" " + value);
			}
			CheckAndAddToDictionary(dictionary, value, key);
		}
	}
}

void CheckAndAddToDictionary(Dictionary& dictionary, const std::string& key, const std::string& value)
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

void ProcessUserInput(std::istream& input, std::ostream& output, const Dictionary& dictionary,
	Dictionary& tempDictionary, const std::string& userInput)
{
	auto it1 = dictionary.find(userInput);
	auto it2 = tempDictionary.find(userInput);
	if (it1 != dictionary.end())
	{
		output << it1->second << "\n\n";
		return;
	}
	else if (it2 != tempDictionary.end())
	{
		output << it2->second << "\n\n";
		return;
	}
	else
	{
		output << "Unknown word \"" + userInput + "\". Enter translation or empty string to cancel.\n";
	}

	ProcessNewWord(input, output, tempDictionary, userInput);
}

void ProcessNewWord(std::istream& input, std::ostream& output, Dictionary& dictionary, const std::string& word)
{
	std::string translation;
	std::getline(input, translation);

	if (translation.empty())
	{
		output << "The word \"" + word + "\" has been ignored.\n\n";
	}
	else
	{
		ToLower(translation);
		CheckAndAddToDictionary(dictionary, word, translation);
		CheckAndAddToDictionary(dictionary, translation, word);

		output << "\nThe word \"" + word + "\" has been saved to dictionary as \"" + translation + "\".\n\n";
	}
}

void ProcessDialogEnding(std::istream& input, std::ostream& output, Dictionary& dictionary,
	const std::string& fileName)
{
	if (dictionary.empty())
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

void SaveChangesToDictionary(const std::string& fileName, Dictionary dictionary)
{
	std::ofstream file(fileName, std::ios::out | std::ios::app);

	if (!file.is_open())
	{
		throw std::runtime_error("Couldn't open file \"" + fileName + "\"");
	}

	std::string str;
	for (auto& pair : dictionary)
	{
		file << "\n"
			 << pair.first;
		std::istringstream iss(pair.second);
		while (iss >> str)
		{
			if (str.back() == ',')
			{
				str = str.substr(0, str.length() - 1);
			}
			file << " " << str;
		}
	}
}

void ToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(),
		[](unsigned char c) { return std::tolower(c); });
}