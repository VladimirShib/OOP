#pragma once

#include "Canvas.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>

class CShapeCreator;

class CShapeApp
{
public:
	CShapeApp(CShapeCreator& creator, CSVGCanvas& canvas, std::istream& input, std::ostream& output);

	bool HandleCommand() const;

private:
	void CreateLine(const std::string& args) const;
	void CreateTriangle(const std::string& args) const;
	void CreateRectangle(const std::string& args) const;
	void CreateCircle(const std::string& args) const;
	void PrintInfo(const std::string&) const;
	void Help(const std::string&) const;
	void DeleteShapes(const std::string&) const;
	void DrawShapes(const std::string&) const;
	void ClearCanvas(const std::string&) const;

private:
	using Handler = std::function<void(const std::string& args)>;
	using ActionMap = std::map<std::string, Handler>;

	CShapeCreator& m_creator;
	CSVGCanvas& m_canvas;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};