#pragma once

#include "ICanvas.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>

class CShapeCreator;

class CShapeApp
{
public:
	CShapeApp(CShapeCreator& creator, ICanvas& canvas, std::istream& input, std::ostream& output);

	bool HandleCommand() const;

private:
	bool CreateLine(const std::string& args) const;
	bool CreateTriangle(const std::string& args) const;
	bool CreateRectangle(const std::string& args) const;
	bool CreateCircle(const std::string& args) const;
	bool PrintInfo(const std::string&) const;
	bool Help(const std::string&) const;
	bool DeleteShapes(const std::string&) const;
	bool DrawShapes(const std::string&) const;
	bool ClearCanvas(const std::string&) const;

private:
	using Handler = std::function<bool(const std::string& args)>;
	using ActionMap = std::map<std::string, Handler>;

	CShapeCreator& m_creator;
	ICanvas& m_canvas;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};