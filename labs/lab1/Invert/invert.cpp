#include "stdafx.h"

constexpr int MATRIX_SIZE_TWO = 2;
constexpr int MATRIX_SIZE_THREE = 3;

using Matrix2x2 = std::array<std::array<double, MATRIX_SIZE_TWO>, MATRIX_SIZE_TWO>;
using Matrix3x3 = std::array<std::array<double, MATRIX_SIZE_THREE>, MATRIX_SIZE_THREE>;

Matrix3x3 GetMatrixFromFile(const std::string& fileName);
Matrix3x3 ReadMatrix(std::ifstream& file);
Matrix3x3 InvertMatrix(const Matrix3x3& matrix);
double FindDeterminantOfMatrix3x3(const Matrix3x3& matrix);
Matrix2x2 GetMatrix2x2(const Matrix3x3& matrix3x3, size_t rowToCrossOut, size_t columnToCrossOut);
double FindDeterminantOfMatrix2x2(const Matrix2x2& matrix);
Matrix3x3 GetMatrixOfMinors(const Matrix3x3& matrix);
Matrix3x3 GetAdjugateMatrix(const Matrix3x3& matrix);
Matrix3x3 TransposeMatrix(const Matrix3x3& matrix);
Matrix3x3 MultiplyMatrixByNumber(const Matrix3x3& matrix, double number);
void PrintMatrix(const Matrix3x3& matrix);
std::string FormatDouble(double value);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: invert.exe <matrix file>\n";

		return 1;
	}

	try
	{
		Matrix3x3 matrix = GetMatrixFromFile(argv[1]);
		PrintMatrix(InvertMatrix(matrix));
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";

		return 1;
	}

	return 0;
}

Matrix3x3 GetMatrixFromFile(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);
	if (file.is_open())
	{
		Matrix3x3 matrix = ReadMatrix(file);
		file.close();
		return matrix;
	}

	throw std::runtime_error("Couldn't open file \"" + fileName + "\"\n");
}

Matrix3x3 ReadMatrix(std::ifstream& file)
{
	Matrix3x3 matrix;
	std::string line;

	for (size_t i = 0; i < MATRIX_SIZE_THREE; ++i)
	{
		if (std::getline(file, line))
		{
			std::istringstream iss(line);
			double number;
			for (size_t j = 0; j < MATRIX_SIZE_THREE; ++j)
			{
				if (iss >> number)
				{
					matrix[i][j] = number;
				}
				else
				{
					throw std::invalid_argument("Unsupported matrix size or invalid input\n"
												"Matrix should be 3x3 and contain valid numbers\n");
				}
			}
		}
		else
		{
			throw std::invalid_argument("Unsupported matrix size or invalid input\n"
										"Matrix should be 3x3 and contain valid numbers\n");
		}
	}

	return matrix;
}

Matrix3x3 InvertMatrix(const Matrix3x3& matrix)
{
	double determinant = FindDeterminantOfMatrix3x3(matrix);
	if (determinant != 0.0)
	{
		Matrix3x3 adjugateMatrix = GetAdjugateMatrix(GetMatrixOfMinors(matrix));

		return MultiplyMatrixByNumber(adjugateMatrix, 1 / determinant);
	}

	throw std::invalid_argument("Matrix's determinant is zero, inversion isn't possible\n");
}

double FindDeterminantOfMatrix3x3(const Matrix3x3& matrix)
{
	double a = FindDeterminantOfMatrix2x2(GetMatrix2x2(matrix, 0, 0));
	double b = FindDeterminantOfMatrix2x2(GetMatrix2x2(matrix, 0, 1));
	double c = FindDeterminantOfMatrix2x2(GetMatrix2x2(matrix, 0, 2));

	return matrix[0][0] * a - matrix[0][1] * b + matrix[0][2] * c;
}

Matrix2x2 GetMatrix2x2(const Matrix3x3& matrix3x3, size_t rowToCrossOut, size_t columnToCrossOut)
{
	std::queue<double> tempStorage;
	for (size_t i = 0; i < MATRIX_SIZE_THREE; ++i)
	{
		for (size_t j = 0; j < MATRIX_SIZE_THREE; ++j)
		{
			if (i != rowToCrossOut && j != columnToCrossOut)
			{
				tempStorage.push(matrix3x3[i][j]);
			}
		}
	}

	Matrix2x2 matrix2x2;
	for (size_t i = 0; i < MATRIX_SIZE_TWO; ++i)
	{
		for (size_t j = 0; j < MATRIX_SIZE_TWO; ++j)
		{
			matrix2x2[i][j] = tempStorage.front();
			tempStorage.pop();
		}
	}

	return matrix2x2;
}

double FindDeterminantOfMatrix2x2(const Matrix2x2& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

Matrix3x3 GetMatrixOfMinors(const Matrix3x3& matrix)
{
	Matrix3x3 matrixOfMinors;
	for (size_t i = 0; i < MATRIX_SIZE_THREE; ++i)
	{
		for (size_t j = 0; j < MATRIX_SIZE_THREE; ++j)
		{
			matrixOfMinors[i][j] = FindDeterminantOfMatrix2x2(GetMatrix2x2(matrix, i, j));
		}
	}

	return matrixOfMinors;
}

Matrix3x3 GetAdjugateMatrix(const Matrix3x3& matrix)
{
	Matrix3x3 newMatrix = matrix;
	newMatrix[0][1] *= -1;
	newMatrix[1][0] *= -1;
	newMatrix[1][2] *= -1;
	newMatrix[2][1] *= -1;

	return TransposeMatrix(newMatrix);
}

Matrix3x3 TransposeMatrix(const Matrix3x3& matrix)
{
	Matrix3x3 transposedMatrix;
	for (size_t i = 0; i < MATRIX_SIZE_THREE; ++i)
	{
		for (size_t j = 0; j < MATRIX_SIZE_THREE; ++j)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}

	return transposedMatrix;
}

Matrix3x3 MultiplyMatrixByNumber(const Matrix3x3& matrix, double number)
{
	Matrix3x3 newMatrix;
	for (size_t i = 0; i < MATRIX_SIZE_THREE; ++i)
	{
		for (size_t j = 0; j < MATRIX_SIZE_THREE; ++j)
		{
			newMatrix[i][j] = matrix[i][j] * number;
		}
	}

	return newMatrix;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (size_t i = 0; i < MATRIX_SIZE_THREE; ++i)
	{
		for (size_t j = 0; j < MATRIX_SIZE_THREE; ++j)
		{
			std::cout << FormatDouble(matrix[i][j]) << ((j + 1) % MATRIX_SIZE_THREE == 0 ? "\n" : "\t");
		}
	}
}

std::string FormatDouble(double value)
{
	std::string str = std::to_string(value);

	size_t dotPosition = str.find('.');
	if (dotPosition != std::string::npos)
	{
		str.erase(dotPosition + 4);
		size_t lastNonZero = str.find_last_not_of('0');
		if (lastNonZero > dotPosition)
		{
			str.erase(lastNonZero + 1);
		}
		else
		{
			str.erase(dotPosition);
		}
	}

	return str;
}