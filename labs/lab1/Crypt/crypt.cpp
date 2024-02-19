#include "stdafx.h"

constexpr uint8_t MAX_KEY_VALUE = 255;

uint8_t GetKey(const std::string& str);
uint8_t MultiplySafely(uint8_t multiplicand, uint8_t multiplier);
uint8_t AddSafely(uint8_t augend, uint8_t addend);
uint8_t CharacterToNumber(char ch, uint8_t radix);
void TransformFile(const std::string& inputFileName, const std::string& outputFileName, uint8_t key, bool encrypting);
char EncryptByte(char ch, uint8_t key);
char DecryptByte(char ch, uint8_t key);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: crypt.exe crypt <input file> <output file> <key> for encrypting\n"
				  << "       crypt.exe decrypt <input file> <output file> <key> for decrypting\n";

		return 1;
	}

	try
	{
		std::string inputFileName(argv[2]);
		std::string outputFileName(argv[3]);
		uint8_t key = GetKey(argv[4]);

		if (std::string(argv[1]) == "crypt")
		{
			TransformFile(inputFileName, outputFileName, key, true);
		}
		else if (std::string(argv[1]) == "decrypt")
		{
			TransformFile(inputFileName, outputFileName, key, false);
		}
		else
		{
			throw std::invalid_argument("Invalid operation. Use \"crypt\" or \"decrypt\"");
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}

uint8_t GetKey(const std::string& str)
{
	if (str.empty())
	{
		throw std::invalid_argument("Invalid key. It should be a number within [0; 255] range");
	}

	uint8_t key = 0;
	constexpr uint8_t RADIX = 10;

	for (size_t i = 0; i < str.length(); ++i)
	{
		key = MultiplySafely(key, RADIX);
		key = AddSafely(key, CharacterToNumber(str[i], RADIX));
	}

	return key;
}

uint8_t MultiplySafely(uint8_t multiplicand, uint8_t multiplier)
{
	if (multiplicand <= MAX_KEY_VALUE / multiplier)
	{
		return multiplicand *= multiplier;
	}
	else
	{
		throw std::overflow_error("Max key value is 255");
	}
}

uint8_t AddSafely(uint8_t augend, uint8_t addend)
{
	if (augend <= MAX_KEY_VALUE - addend)
	{
		return augend += addend;
	}
	else
	{
		throw std::overflow_error("Max key value is 255");
	}
}

uint8_t CharacterToNumber(char ch, uint8_t radix)
{
	if (std::isdigit(ch))
	{
		return ch - '0';
	}
	else
	{
		throw std::invalid_argument("Invalid key. It should be a number within [0; 255] range");
	}
}

void TransformFile(const std::string& inputFileName, const std::string& outputFileName, uint8_t key, bool encrypting)
{
	static_assert(sizeof(char) == sizeof(uint8_t));

	std::ifstream inputFile(inputFileName, std::ios::binary);
	std::ofstream outputFile(outputFileName, std::ios::binary);
	if (!inputFile.is_open() || !outputFile.is_open())
	{
		throw std::runtime_error("Couldn't open input or output file");
	}

	std::transform(
		std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(outputFile),
		[key, encrypting](char ch) {
			if (encrypting)
			{
				return EncryptByte(ch, key);
			}
			else
			{
				return DecryptByte(ch, key);
			}
		}
	);
}

char EncryptByte(char ch, uint8_t key)
{
	ch ^= key;

	const uint8_t maskFor7 = 0b10000000;
	const uint8_t maskFor65 = 0b01100000;
	const uint8_t maskFor43 = 0b00011000;
	const uint8_t maskFor210 = 0b00000111;

	uint8_t move7 = (ch & maskFor7) >> 2;
	uint8_t move65 = (ch & maskFor65) >> 5;
	uint8_t move43 = (ch & maskFor43) << 3;
	uint8_t move210 = (ch & maskFor210) << 2;

	return move7 | move65 | move43 | move210;
}

char DecryptByte(char ch, uint8_t key)
{
	const uint8_t maskFor76 = 0b11000000;
	const uint8_t maskFor5 = 0b00100000;
	const uint8_t maskFor432 = 0b00011100;
	const uint8_t maskFor10 = 0b00000011;

	uint8_t move76 = (ch & maskFor76) >> 3;
	uint8_t move5 = (ch & maskFor5) << 2;
	uint8_t move432 = (ch & maskFor432) >> 2;
	uint8_t move10 = (ch & maskFor10) << 5;

	return (move76 | move5 | move432 | move10) ^ key;
}