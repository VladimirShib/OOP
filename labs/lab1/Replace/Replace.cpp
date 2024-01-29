#include "stdafx.h"

bool FilesAreNotOpen(const std::ifstream& firstFile, const std::ofstream& secondFile);
void CopyFileWithReplacement(std::ifstream& inputFile, std::ofstream& outputFile,
	const std::string& searchString, const std::string& replacementString);
void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString);
std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(argv[1]);

	std::ofstream outputFile;
	outputFile.open(argv[2]);

	if (FilesAreNotOpen(inputFile, outputFile))
	{
		std::cout << "Failed to open one or both files\n";
		return 1;
	}

	std::string search = argv[3];
	std::string replace = argv[4];

	CopyFileWithReplacement(inputFile, outputFile, search, replace);

	return 0;
}

bool FilesAreNotOpen(const std::ifstream& firstFile, const std::ofstream& secondFile)
{
	if (!firstFile.is_open() || !secondFile.is_open())
	{
		return true;
	}
	return false;
}

void CopyFileWithReplacement(std::ifstream& inputFile, std::ofstream& outputFile,
	const std::string& searchString, const std::string& replacementString)
{
	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);
	outputFile.flush();
	inputFile.close();
	outputFile.close();
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
	}
}

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);

		if (foundPos != std::string::npos)
		{
			result.append(subject, pos, foundPos - pos);
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			result.append(subject, pos, subject.length());
			pos = subject.length();
		}
	}
	return result;
}