#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <string>

class CCalculatorEngine;

class CCalculatorApp
{
public:
	CCalculatorApp(CCalculatorEngine& engine, std::istream& input, std::ostream& output);

	bool HandleCommand() const;

private:
	bool DeclareVar(const std::string& name);
	bool DefineVar(const std::string& args);
	bool DefineFn(const std::string& args);
	bool PrintValue(const std::string& name);
	bool PrintVars(const std::string&);
	bool PrintFns(const std::string&);
	bool Help(const std::string&) const;

private:
	using Handler = std::function<bool(const std::string& args)>;
	using ActionMap = std::map<std::string, Handler>;

	CCalculatorEngine& m_engine;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};