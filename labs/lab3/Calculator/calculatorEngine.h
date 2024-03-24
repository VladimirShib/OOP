#pragma once
#include "IValue.h"
#include "variable.h"
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <string>

class CCalculatorEngine
{
private:
	using Function = std::function<double(const double, const double)>;
	using EnumFn = std::function<void(const std::string& name, const double value)>;

	bool IdentifierExists(const std::string& name) const;
	std::optional<IValue*> FindValue(const std::string& name);
	void ResetFnValues();

public:
	bool DeclareVar(const std::string& name);
	bool DefineVarWithIdentifier(const std::string& name, const std::string& value);
	bool DefineVarWithNumber(const std::string& name, const std::string& value);
	bool DefineUnaryFn(const std::string& name, const std::string& value);
	bool DefineBinaryFn(
		const std::string& name,
		const std::string& leftOperand,
		const std::string& rightOperand,
		Function&& fn);
	std::optional<double> GetValue(const std::string& name);
	void EnumVariables(const EnumFn& fn) const;
	void EnumFunctions(const EnumFn& fn) const;

private:
	std::map<std::string, CVariable> m_variables;
	std::map<std::string, std::unique_ptr<IValue>> m_functions;
};