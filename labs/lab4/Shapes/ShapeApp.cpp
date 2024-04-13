#include "ShapeApp.h"
#include "Color.h"
#include "IShape.h"
#include "Point.h"
#include "ShapeCreator.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <regex>
#include <sstream>
#include <vector>

namespace
{

using Shapes = std::vector<std::unique_ptr<IShape>>;

const std::string canvasFile = "D://Study//OOP//labs//lab4//Shapes//canvas.svg";

struct LineArgs
{
	CPoint start;
	CPoint end;
	std::uint32_t color = 0;
};

struct TriangleArgs
{
	CPoint p1;
	CPoint p2;
	CPoint p3;
	std::uint32_t outline = 0;
	std::uint32_t fill = 0;
};

struct RectangleArgs
{
	CPoint topLeft;
	double width = 0;
	double height = 0;
	std::uint32_t outline = 0;
	std::uint32_t fill = 0;
};

struct CircleArgs
{
	CPoint center;
	double radius = 0;
	std::uint32_t outline = 0;
	std::uint32_t fill = 0;
};

std::uint32_t GetColorFromStreamOrDefault(std::istream& is, std::uint32_t defaultColor)
{
	std::string colorStr;
	if (is >> colorStr)
	{
		if (std::regex_match(colorStr, std::regex("^[A-Fa-f0-9]{2}$")))
		{
			return std::stoul(colorStr + colorStr + colorStr, nullptr, 16);
		}

		if (std::regex_match(colorStr, std::regex("^[A-Fa-f0-9]{6,8}$")))
		{
			return std::stoul(colorStr, nullptr, 16);
		}
	}

	return defaultColor;
}

bool ParseLineArgs(const std::string& args, LineArgs& line)
{
	std::istringstream iss(args);
	if (!(iss >> line.start.x >> line.start.y >> line.end.x >> line.end.y))
	{
		return false;
	}

	line.color = GetColorFromStreamOrDefault(iss, 0);

	return true;
}

bool ParseTriangleArgs(const std::string& args, TriangleArgs& triangle)
{
	std::istringstream iss(args);
	if (!(iss >> triangle.p1.x >> triangle.p1.y >> triangle.p2.x >> triangle.p2.y
			>> triangle.p3.x >> triangle.p3.y))
	{
		return false;
	}

	triangle.outline = GetColorFromStreamOrDefault(iss, 0);
	triangle.fill = GetColorFromStreamOrDefault(iss, 0xffffff);

	return true;
}

bool ParseRectangleArgs(const std::string& args, RectangleArgs& rectangle)
{
	std::istringstream iss(args);
	if (!(iss >> rectangle.topLeft.x >> rectangle.topLeft.y >> rectangle.width >> rectangle.height))
	{
		return false;
	}
	if (rectangle.width <= 0 || rectangle.height <= 0)
	{
		return false;
	}

	rectangle.outline = GetColorFromStreamOrDefault(iss, 0);
	rectangle.fill = GetColorFromStreamOrDefault(iss, 0xffffff);

	return true;
}

bool ParseCircleArgs(const std::string& args, CircleArgs& circle)
{
	std::istringstream iss(args);
	if (!(iss >> circle.center.x >> circle.center.y >> circle.radius))
	{
		return false;
	}
	if (circle.radius <= 0)
	{
		return false;
	}

	circle.outline = GetColorFromStreamOrDefault(iss, 0);
	circle.fill = GetColorFromStreamOrDefault(iss, 0xffffff);

	return true;
}

std::string GetMaxAreaShapeInfo(const Shapes& shapes)
{
	assert(!shapes.empty());

	auto maxAreaShape = std::max_element(shapes.begin(), shapes.end(),
		[](const auto& a, const auto& b) {
			return a->GetArea() < b->GetArea();
		});

	return (*maxAreaShape)->ToString();
}

std::string GetMinPerimeterShapeInfo(const Shapes& shapes)
{
	assert(!shapes.empty());

	auto minPerimeterShape = std::min_element(shapes.begin(), shapes.end(),
		[](const auto& a, const auto& b) {
			return a->GetPerimeter() < b->GetPerimeter();
		});

	return (*minPerimeterShape)->ToString();
}

} // namespace

CShapeApp::CShapeApp(CShapeCreator& creator, CSVGCanvas& canvas, std::istream& input, std::ostream& output)
	: m_creator(creator)
	, m_canvas(canvas)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "line", std::bind_front(&CShapeApp::CreateLine, this) },
		  { "triangle", std::bind_front(&CShapeApp::CreateTriangle, this) },
		  { "rectangle", std::bind_front(&CShapeApp::CreateRectangle, this) },
		  { "circle", std::bind_front(&CShapeApp::CreateCircle, this) },
		  { "info", std::bind_front(&CShapeApp::PrintInfo, this) },
		  { "help", std::bind_front(&CShapeApp::Help, this) },
		  { "delete", std::bind_front(&CShapeApp::DeleteShapes, this) },
		  { "draw", std::bind_front(&CShapeApp::DrawShapes, this) },
		  { "clear", std::bind_front(&CShapeApp::ClearCanvas, this) } })
{
}

bool CShapeApp::HandleCommand() const
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

	it->second(args);
	return true;
}

void CShapeApp::CreateLine(const std::string& args) const
{
	LineArgs lineArgs;
	if (!::ParseLineArgs(args, lineArgs))
	{
		m_output << "Invalid arguments for line\n"
				 << "Usage: line <x1> <y1> <x2> <y2> <[optional] color>\n";
	}
	else
	{
		m_creator.CreateLine(lineArgs.start, lineArgs.end, lineArgs.color);
	}
}

void CShapeApp::CreateTriangle(const std::string& args) const
{
	TriangleArgs triangleArgs;
	if (!::ParseTriangleArgs(args, triangleArgs))
	{
		m_output << "Invalid arguments for triangle\n"
				 << "Usage: triangle <x1> <y1> <x2> <y2> <x3> <y3> <[optional] outline color> <[optional] fill color>\n";
	}
	else
	{
		m_creator.CreateTriangle(
			triangleArgs.p1,
			triangleArgs.p2,
			triangleArgs.p3,
			triangleArgs.outline,
			triangleArgs.fill);
	}
}

void CShapeApp::CreateRectangle(const std::string& args) const
{
	RectangleArgs rectangleArgs;
	if (!::ParseRectangleArgs(args, rectangleArgs))
	{
		m_output << "Invalid arguments for rectangle\n"
				 << "Usage: rectangle <top-left x> <top-left y> <width> <height> "
				 << "<[optional] outline color> <[optional] fill color>\n";
	}
	else
	{
		m_creator.CreateRectangle(
			rectangleArgs.topLeft,
			rectangleArgs.width,
			rectangleArgs.height,
			rectangleArgs.outline,
			rectangleArgs.fill);
	}
}

void CShapeApp::CreateCircle(const std::string& args) const
{
	CircleArgs circleArgs;
	if (!::ParseCircleArgs(args, circleArgs))
	{
		m_output << "Invalid arguments for circle\n"
				 << "Usage: circle <center x> <center y> <radius> <[optional] outline color> <[optional] fill color>\n";
	}
	else
	{
		m_creator.CreateCircle(circleArgs.center, circleArgs.radius, circleArgs.outline, circleArgs.fill);
	}
}

void CShapeApp::PrintInfo(const std::string&) const
{
	const Shapes& shapes = m_creator.GetShapes();
	if (shapes.empty())
	{
		m_output << "No shapes\n";
	}
	else
	{
		m_output << "Max area shape:\n";
		m_output << ::GetMaxAreaShapeInfo(shapes) << "\n\n";
		m_output << "Min perimeter shape:\n";
		m_output << ::GetMinPerimeterShapeInfo(shapes) << "\n"
				 << std::endl;
	}
}

void CShapeApp::Help(const std::string&) const
{
	m_output << "Available shapes: line, triangle, rectangle, circle\n";
	m_output << "Usage:\n";
	m_output << "line <x1> <y1> <x2> <y2> <[optional] color>\n";
	m_output << "triangle <x1> <y1> <x2> <y2> <x3> <y3> <[optional] outline color> <[optional] fill color>\n";
	m_output << "rectangle <top-left x> <top-left y> <width> <height> <[optional] outline color> <[optional] fill color>\n";
	m_output << "circle <center x> <center y> <radius> <[optional] outline color> <[optional] fill color>\n";
	m_output << "Color is HEX. Example: ff0000\n";
	m_output << "delete - deletes all shapes\n";
	m_output << "draw - draws all shapes on canvas\n";
	m_output << "clear - clears canvas" << std::endl;
}

void CShapeApp::DeleteShapes(const std::string&) const
{
	m_creator.DeleteShapes();
}

void CShapeApp::DrawShapes(const std::string&) const
{
	const Shapes& shapes = m_creator.GetShapes();
	if (shapes.empty())
	{
		m_output << "No shapes\n";
	}
	else
	{
		ClearCanvas("");

		for (const auto& shape : shapes)
		{
			shape->Draw(m_canvas);
		}

		if (!m_canvas.RenderToFile(canvasFile))
		{
			m_output << "Couldn't open canvas\n";
		}
	}
}

void CShapeApp::ClearCanvas(const std::string&) const
{
	if (!m_canvas.Clear(canvasFile))
	{
		m_output << "Couldn't open canvas\n";
	}
}