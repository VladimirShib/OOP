#include "calculatorApp.h"
#include "calculatorEngine.h"
#include <cctype>
#include <iomanip>
#include <limits>
#include <optional>
#include <regex>
#include <sstream>
#include <utility>

namespace
{

using Function = std::function<double(const double, const double)>;

std::optional<Function> GetFunction(const std::string& operation)
{
	if (operation.size() != 1)
	{
		return std::nullopt;
	}

	switch (operation[0])
	{
	case '+':
		return [](const double first, const double second) {
			return first + second;
		};
	case '-':
		return [](const double first, const double second) {
			return first - second;
		};
	case '*':
		return [](const double first, const double second) {
			return first * second;
		};
	case '/':
		return [](const double first, const double second) {
			return second == 0
				? std::numeric_limits<double>::quiet_NaN()
				: first / second;
		};
	default:
		return std::nullopt;
	}
}

} // namespace

CCalculatorApp::CCalculatorApp(CCalculatorEngine& engine, std::istream& input, std::ostream& output)
	: m_engine(engine)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", std::bind_front(&CCalculatorApp::DeclareVar, this) },
		  { "let", std::bind_front(&CCalculatorApp::DefineVar, this) },
		  { "fn", std::bind_front(&CCalculatorApp::DefineFn, this) },
		  { "print", std::bind_front(&CCalculatorApp::PrintValue, this) },
		  { "printvars", std::bind_front(&CCalculatorApp::PrintVars, this) },
		  { "printfns", std::bind_front(&CCalculatorApp::PrintFns, this) },
		  { "Help", std::bind_front(&CCalculatorApp::Help, this) } })
{
}

bool CCalculatorApp::HandleCommand() const
{
	std::string command;
	std::getline(m_input, command);
	std::istringstream iss(command);

	std::string action;
	iss >> action;

	std::string args;
	std::getline(iss >> std::ws, args);

	auto it = m_actionMap.find(action);
	if (it == m_actionMap.end())
	{
		return false;
	}

	return it->second(args);
}

bool CCalculatorApp::DeclareVar(const std::string& name)
{
	if (name.empty() || !std::regex_match(name, std::regex("^[A-Za-z_][A-Za-z0-9_]*$")))
	{
		m_output << "Invalid variable name.\n";
	}
	else if (!m_engine.DeclareVar(name))
	{
		m_output << "Error: redeclaration of variable `" << name << "`.\n";
	}

	return true;
}

bool CCalculatorApp::DefineVar(const std::string& args)
{
	std::smatch match;
	std::regex pattern("^([A-Za-z_][A-Za-z0-9_]*)\\s*=\\s*([A-Za-z0-9_.]+)$");

	if (args.empty() || !std::regex_match(args, match, pattern))
	{
		m_output << "Invalid definition.\n";
	}
	else if (std::string value(match[2]); std::regex_match(value, std::regex("^[A-Za-z_][A-Za-z0-9_]*$")))
	{
		if (!m_engine.DefineVarWithIdentifier(match[1], value))
		{
			m_output << "Error: invalid definition of variable `" << match[1] << "`.\n";
		}
	}
	else
	{
		if (!m_engine.DefineVarWithNumber(match[1], value))
		{
			m_output << "Error: invalid definition of variable `" << match[1] << "`.\n";
		}
	}

	return true;
}

bool CCalculatorApp::DefineFn(const std::string& args)
{
	std::smatch match;
	std::regex unaryFn("^([A-Za-z_][A-Za-z0-9_]*)\\s*=\\s*([A-Za-z_][A-Za-z0-9_]*)$");
	std::regex binaryFn("^([A-Za-z_][A-Za-z0-9_]*)\\s*=\\s*([A-Za-z_][A-Za-z0-9_]*)\\s*([+\\-*\\/]){1}\\s*([A-Za-z_][A-Za-z0-9_]*)$");

	if (std::regex_match(args, match, unaryFn))
	{
		if (!m_engine.DefineUnaryFn(match[1], match[2]))
		{
			m_output << "Error: the function is already defined or the identifier was not found.\n";
		}
	}
	else if (std::regex_match(args, match, binaryFn))
	{
		auto function = ::GetFunction(match[3]);
		if (!function.has_value())
		{
			m_output << "Error: invalid operation.\n";
		}
		else if (!m_engine.DefineBinaryFn(match[1], match[2], match[4], std::move(*function)))
		{
			m_output << "Error: the function is already defined or the identifier was not found.\n";
		}
	}
	else
	{
		m_output << "Invalid definition.\n";
	}

	return true;
}

bool CCalculatorApp::PrintValue(const std::string& name)
{
	if (name.empty() || !std::regex_match(name, std::regex("^[A-Za-z_][A-Za-z0-9_]*$")))
	{
		m_output << "Invalid identifier.\n";
		return true;
	}

	auto value = m_engine.GetValue(name);
	if (!value.has_value())
	{
		m_output << "Error: `" << name << "` has not been declared.\n";
	}
	else
	{
		m_output << std::fixed << std::setprecision(2) << *value << "\n";
	}

	return true;
}

bool CCalculatorApp::PrintVars(const std::string&)
{
	m_output << std::fixed << std::setprecision(2);
	m_engine.EnumVariables([this](const std::string& name, const double value) {
		m_output << name << " : " << value << "\n";
	});

	m_output.flush();
	std::cout << std::defaultfloat;

	return true;
}

bool CCalculatorApp::PrintFns(const std::string&)
{
	m_output << std::fixed << std::setprecision(2);
	m_engine.EnumFunctions([this](const std::string& name, const double value) {
		m_output << name << " : " << value << "\n";
	});

	m_output.flush();
	std::cout << std::defaultfloat;

	return true;
}

bool CCalculatorApp::Help(const std::string&) const
{
	m_output << "Available commands:\n\n";
	m_output << "var <identifier>\n";
	m_output << "let <identifier>=<floating point number>\n";
	m_output << "let <identifier1>=<identifier2>\n";
	m_output << "fn <identifier1>=<identifier2>\n";
	m_output << "fn <identifier1>=<identifier2><operation><identifier3>\n";
	m_output << "print <identifier>\n";
	m_output << "printvars\n";
	m_output << "printfns\n"
			 << std::endl;

	return true;
}