#include "stdafx.h"
#include <cassert>

constexpr int MAX_RADIX = 36;
constexpr int MIN_RADIX = 2;
constexpr int DECIMAL = 10;

struct Arguments
{
	int sourceNotation;
	int destinationNotation;
	std::string value;
};

Arguments ParseArguments(int argc, char* argv[]);
int GetRadixFromString(const std::string& notation);
std::string ConvertValueToAnotherRadix(const std::string& valueStr,
	int sourceNotation, int destinationNotation);
int StringToInt(const std::string& str, int radix);
int CharacterToNumber(char ch, int radix);
std::string IntToString(int number, int radix);
char NumberToCharacter(int number);
int MultiplySafely(int multiplicand, int multiplier);
int AddSafely(int augend, int addend);
bool IsRadixValid(int radix);

int main(int argc, char* argv[])
{
	try
	{
		Arguments args = ParseArguments(argc, argv);
		std::cout << ConvertValueToAnotherRadix(args.value, args.sourceNotation, args.destinationNotation);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}

Arguments ParseArguments(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::invalid_argument(
			"Invalid argument count\n"
			"Usage: radix.exe <source notation> <destination notation> <value>"
		);
	}

	Arguments args;
	args.sourceNotation = GetRadixFromString(argv[1]);
	args.destinationNotation = GetRadixFromString(argv[2]);
	args.value = argv[3];

	return args;
}

int GetRadixFromString(const std::string& str)
{
	int radix = StringToInt(str, DECIMAL);
	if (!IsRadixValid(radix))
	{
		throw std::invalid_argument(
			"Source or destination notation is invalid\n"
			"Acceptable notations: [2; 36]"
		);
	}

	return radix;
}

std::string ConvertValueToAnotherRadix(const std::string& valueStr,
	int sourceNotation, int destinationNotation)
{
	int value = StringToInt(valueStr, sourceNotation);

	return IntToString(value, destinationNotation);
}

int StringToInt(const std::string& str, int radix)
{
	if (!IsRadixValid(radix))
	{
		throw std::out_of_range("Radix is out of range");
	}

	if (str.empty() || (str[0] == '-' && str.length() == 1))
	{
		throw std::invalid_argument("Arguments should be valid numbers");
	}

	bool isNegative = (str[0] == '-');
	int number = 0;
	for (size_t i = (isNegative ? 1 : 0); i < str.length(); ++i)
	{
		number = MultiplySafely(number, radix);
		number = AddSafely(number, CharacterToNumber(str[i], radix));
	}
	
	return (isNegative ? -number : number);
}

int CharacterToNumber(char ch, int radix)
{
	assert(IsRadixValid(radix));

	if (std::isalpha(ch) && ch >= 'A' && ch < 'A' + radix - DECIMAL)
	{
		return ch + DECIMAL - 'A';
	}
	if (std::isdigit(ch) && ch >= '0' && ch < '0' + radix)
	{
		return ch - '0';
	}

	throw std::invalid_argument(
		"One or more arguments are invalid\n"
		"Acceptable notations: [2; 36]\n"
		"Value's radix should match provided source notation\n"
		"Letters should be uppercase"
	);
}

std::string IntToString(int number, int radix)
{
	std::string valueStr;
	bool isNegative = number < 0;
	if (isNegative)
	{
		number *= -1;
	}
	
	do
	{
		int digit = number % radix;
		valueStr.push_back(NumberToCharacter(digit));
		number /= radix;
	}
	while (number != 0);

	if (isNegative)
	{
		valueStr.push_back('-');
	}

	std::reverse(valueStr.begin(), valueStr.end());

	return valueStr;
}

char NumberToCharacter(int number)
{
	if (number >= 0 && number <= 9)
	{
		return '0' + number;
	}
	else
	{
		return 'A' + number - DECIMAL;
	}
}

int MultiplySafely(int multiplicand, int multiplier)
{
	if (multiplicand <= std::numeric_limits<int>::max() / multiplier)
	{
		return multiplicand *= multiplier;
	}
	else
	{
		throw std::overflow_error("Value is too large");
	}
}

int AddSafely(int augend, int addend)
{
	if (augend <= std::numeric_limits<int>::max() - addend)
	{
		return augend += addend;
	}
	else
	{
		throw std::overflow_error("Value is too large");
	}
}

bool IsRadixValid(int radix)
{
	return radix >= MIN_RADIX && radix <= MAX_RADIX;
}