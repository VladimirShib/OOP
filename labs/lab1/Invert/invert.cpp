#include "stdafx.h"

constexpr int MATRIX_SIZE_TWO = 2;
constexpr int MATRIX_SIZE_THREE = 3;

using Matrix2x2 = std::array<std::array<double, MATRIX_SIZE_TWO>, MATRIX_SIZE_TWO>;
using Matrix3x3 = std::array<std::array<double, MATRIX_SIZE_THREE>, MATRIX_SIZE_THREE>;

Matrix3x3 GetMatrixFromFile(const std::string& fileName);
Matrix3x3 ReadMatrix(std::ifstream& file);
std::optional<Matrix3x3> InvertMatrix(const Matrix3x3& matrix);
double FindDeterminant(const Matrix3x3& matrix);
double FindDeterminant(const Matrix2x2& matrix);
Matrix2x2 GetSubmatrixByRemovingRowAndCol(const Matrix3x3& matrix3x3, size_t rowToRemove, size_t columnToRemove);
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
		
		if (auto invertedMatrix = InvertMatrix(matrix))
		{
			PrintMatrix(*invertedMatrix);
		}
		else
		{
			throw std::invalid_argument("Matrix's determinant is zero, inversion isn't possible");
		}
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
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		throw std::runtime_error("Couldn't open file \"" + fileName + "\"");
	}

	return ReadMatrix(file);
}

Matrix3x3 ReadMatrix(std::ifstream& file)
{
	Matrix3x3 matrix;
	std::string line;

	for (size_t i = 0; i < matrix.size(); ++i)
	{
		if (!std::getline(file, line))
		{
			throw std::invalid_argument("Unsupported matrix size or invalid input\n"
										"Matrix should be 3x3 and contain valid numbers");
		}

		std::istringstream iss(line);
		double number;
		
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			if (iss >> number)
			{
				matrix[i][j] = number;
			}
			else
			{
				throw std::invalid_argument("Unsupported matrix size or invalid input\n"
											"Matrix should be 3x3 and contain valid numbers");
			}
		}
	}

	return matrix;
}

std::optional<Matrix3x3> InvertMatrix(const Matrix3x3& matrix)
{
	double determinant = FindDeterminant(matrix);
	if (determinant == 0.0)
	{
		return std::nullopt;
	}
	Matrix3x3 adjugateMatrix = GetAdjugateMatrix(GetMatrixOfMinors(matrix));
	
	return MultiplyMatrixByNumber(adjugateMatrix, 1 / determinant);
}

double FindDeterminant(const Matrix3x3& matrix)
{
	double a = FindDeterminant(GetSubmatrixByRemovingRowAndCol(matrix, 0, 0));
	double b = FindDeterminant(GetSubmatrixByRemovingRowAndCol(matrix, 0, 1));
	double c = FindDeterminant(GetSubmatrixByRemovingRowAndCol(matrix, 0, 2));

	return matrix[0][0] * a - matrix[0][1] * b + matrix[0][2] * c;
}

double FindDeterminant(const Matrix2x2& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

Matrix2x2 GetSubmatrixByRemovingRowAndCol(const Matrix3x3& matrix3x3, size_t rowToRemove, size_t columnToRemove)
{
	std::queue<double> tempStorage;
	for (size_t i = 0; i < matrix3x3.size(); ++i)
	{
		if (i != rowToRemove)
		{
			for (size_t j = 0; j < matrix3x3.size(); ++j)
			{
				if (j != columnToRemove)
				{
					tempStorage.push(matrix3x3[i][j]);
				}
			}
		}
	}

	Matrix2x2 matrix2x2;
	for (size_t i = 0; i < matrix2x2.size(); ++i)
	{
		for (size_t j = 0; j < matrix2x2.size(); ++j)
		{
			matrix2x2[i][j] = tempStorage.front();
			tempStorage.pop();
		}
	}

	return matrix2x2;
}

Matrix3x3 GetMatrixOfMinors(const Matrix3x3& matrix)
{
	Matrix3x3 matrixOfMinors;
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			matrixOfMinors[i][j] = FindDeterminant(GetSubmatrixByRemovingRowAndCol(matrix, i, j));
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
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}

	return transposedMatrix;
}

Matrix3x3 MultiplyMatrixByNumber(const Matrix3x3& matrix, double number)
{
	Matrix3x3 newMatrix;
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			newMatrix[i][j] = matrix[i][j] * number;
		}
	}

	return newMatrix;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			std::cout << FormatDouble(matrix[i][j]) << ((j + 1) % matrix.size() == 0 ? "\n" : "\t");
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