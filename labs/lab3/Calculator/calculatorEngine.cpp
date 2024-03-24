#include "calculatorEngine.h"
#include "binaryFunction.h"
#include "unaryFunction.h"
#include <limits>
#include <regex>
#include <stdexcept>
#include <utility>

bool CCalculatorEngine::DeclareVar(const std::string& name)
{
	if (IdentifierExists(name))
	{
		return false;
	}

	m_variables.emplace(name, std::numeric_limits<double>::quiet_NaN());
	return true;
}

bool CCalculatorEngine::DefineVarWithIdentifier(const std::string& name, const std::string& value)
{
	std::optional<double> number;
	if (auto var = m_variables.find(value); var != m_variables.end())
	{
		number = var->second.Get();
	}
	else if (auto fn = m_functions.find(value); fn != m_functions.end())
	{
		number = fn->second->Get();
	}
	if (m_functions.contains(name) || !number.has_value())
	{
		return false;
	}

	if (auto key = m_variables.find(name); key != m_variables.end())
	{
		key->second.Set(*number);
	}
	else
	{
		m_variables.emplace(name, *number);
	}

	return true;
}

bool CCalculatorEngine::DefineVarWithNumber(const std::string& name, const std::string& value)
{
	if (m_functions.contains(name))
	{
		return false;
	}

	double number = 0;
	try
	{
		number = std::stod(value);
	}
	catch (...)
	{
		return false;
	}

	auto it = m_variables.find(name);
	if (it == m_variables.end())
	{
		m_variables.emplace(name, number);
	}
	else
	{
		it->second.Set(number);
	}

	ResetFnValues();
	return true;
}

bool CCalculatorEngine::DefineUnaryFn(const std::string& name, const std::string& value)
{
	if (IdentifierExists(name) || !IdentifierExists(value))
	{
		return false;
	}

	m_functions.emplace(name, std::make_unique<CUnaryFunction>(*FindValue(value)));

	return true;
}

bool CCalculatorEngine::DefineBinaryFn(
	const std::string& name,
	const std::string& leftOperand,
	const std::string& rightOperand,
	Function&& fn)
{
	if (IdentifierExists(name) || !IdentifierExists(leftOperand) || !IdentifierExists(rightOperand))
	{
		return false;
	}

	m_functions.emplace(
		name,
		std::make_unique<CBinaryFunction>(*FindValue(leftOperand), *FindValue(rightOperand), std::move(fn)));

	return true;
}

std::optional<double> CCalculatorEngine::GetValue(const std::string& name)
{
	if (auto it = m_variables.find(name); it != m_variables.end())
	{
		return it->second.Get();
	}

	if (auto it = m_functions.find(name); it != m_functions.end())
	{
		return it->second->Get();
	}

	return std::nullopt;
}

bool CCalculatorEngine::IdentifierExists(const std::string& name) const
{
	return m_variables.contains(name) || m_functions.contains(name);
}

std::optional<IValue*> CCalculatorEngine::FindValue(const std::string& name)
{
	if (auto it = m_variables.find(name); it != m_variables.end())
	{
		return &it->second;
	}
	if (auto it = m_functions.find(name); it != m_functions.end())
	{
		return it->second.get();
	}

	return std::nullopt;
}

void CCalculatorEngine::EnumVariables(const EnumFn& fn) const
{
	for (const auto& id : m_variables)
	{
		fn(id.first, id.second.Get());
	}
}

void CCalculatorEngine::EnumFunctions(const EnumFn& fn) const
{
	for (const auto& id : m_functions)
	{
		fn(id.first, id.second->Get());
	}
}

void CCalculatorEngine::ResetFnValues()
{
	for (auto& fn : m_functions)
	{
		fn.second->ResetCurrentValue();
	}
}