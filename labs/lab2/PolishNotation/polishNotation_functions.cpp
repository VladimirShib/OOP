#include "polishNotation_functions.h"
#include <sstream>
#include <locale>
#include <stack>

namespace
{

enum class Operation
{
	ADDITION,
	MULTIPLICATION
};

Operation GetOperation(char ch)
{
	switch (ch)
	{
	case '+':
		return Operation::ADDITION;
	case '*':
		return Operation::MULTIPLICATION;
	default:
		throw std::invalid_argument("ERROR");
	}
}

void Init(std::istream& input, Operation& operation)
{
	char ch;
	input >> ch;

	if (ch != '(')
	{
		throw std::invalid_argument("ERROR");
	}

	if (input >> ch)
	{
		operation = GetOperation(ch);
	}

	if (input >> ch && ch == ')')
	{
		throw std::invalid_argument("ERROR");
	}

	input.unget();
}

void ValidateChar(std::istream& input, char ch)
{
	if (std::isdigit(ch))
	{
		input.unget();
		return;
	}

	if (ch == '-')
	{
		if (input >> ch && std::isdigit(ch))
		{
			input.unget();
			input.unget();
			return;
		}
	}

	throw std::invalid_argument("ERROR");
}

int ApplyOperation(int result, const int value, const Operation& operation)
{
	if (operation == Operation::ADDITION)
	{
		result += value;
	}
	else
	{
		result *= value;
	}

	return result;
}

int DoCalculations(std::istream& input)
{
	std::stack<Operation> operations;
	std::stack<int> tempResult;

	char ch;
	Operation operation;
	Init(input, operation);
	int result = (operation == Operation::ADDITION) ? 0 : 1;

	while (input >> ch)
	{
		if (ch == '(')
		{
			operations.push(operation);
			tempResult.push(result);
			if (input >> ch)
			{
				operation = GetOperation(ch);

				if (input >> ch && ch == ')')
				{
					throw std::invalid_argument("ERROR");
				}
				input.unget();
			}
			result = (operation == Operation::ADDITION) ? 0 : 1;

			continue;
		}
		else if (ch == ')')
		{
			if (!operations.empty())
			{
				operation = operations.top();
				operations.pop();
				result = ApplyOperation(result, tempResult.top(), operation);
				tempResult.pop();

				continue;
			}
			else
			{
				return result;
			}
		}

		ValidateChar(input, ch);
		int value;
		input >> value;
		result = ApplyOperation(result, value, operation);
	}

	throw std::invalid_argument("ERROR");
}

} // namespace

int CaculateExpression(const std::string& expression)
{
	if (expression.empty())
	{
		throw std::invalid_argument("ERROR");
	}

	std::istringstream input(expression);

	return DoCalculations(input);
}