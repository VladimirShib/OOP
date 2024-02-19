#include "stdafx.h"

bool FilesAreOpen(const std::ifstream& firstFile, const std::ofstream& secondFile);
void CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName,
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

	std::string inputFileName = argv[1];
	std::string outputFileName = argv[2];
	std::string search = argv[3];
	std::string replace = argv[4];

	try
	{
		CopyFileWithReplacement(inputFileName, outputFileName, search, replace);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}

bool FilesAreOpen(const std::ifstream& firstFile, const std::ofstream& secondFile)
{
	return firstFile.is_open() && secondFile.is_open();
}

void CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName,
	const std::string& searchString, const std::string& replacementString)
{
	std::ifstream inputFile(inputFileName);
	std::ofstream outputFile(outputFileName);

	if (!FilesAreOpen(inputFile, outputFile))
	{
		throw std::runtime_error("Failed to open one or both files");
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replacementString);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Couldn't flush output");
	}
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
		result.append(subject, pos, foundPos - pos);

		if (foundPos == std::string::npos)
		{
			break;
		}

		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}