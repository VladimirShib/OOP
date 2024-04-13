#include "Canvas.h"
#include "Color.h"
#include "fstream"
#include <format>

namespace
{

const std::string header = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\n";
const std::string opening = "<svg width=\"1000px\" height=\"800px\" xmlns=\"http://www.w3.org/2000/svg\">\n\n";
const std::string closing = "\n</svg>";
const std::string strokeWidth = ";stroke-width:3";

} // namespace

bool CSVGCanvas::RenderToFile(const std::string& fileName)
{
	std::ofstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	file << header << opening;
	for (const auto& shape : m_shapes)
	{
		file << shape;
	}
	file << closing;

	return true;
}

bool CSVGCanvas::Clear(const std::string& fileName)
{
	m_shapes.clear();

	std::ofstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	file << header << opening << closing;

	return true;
}

void CSVGCanvas::DrawLine(CPoint start, CPoint end, std::optional<std::uint32_t> color)
{
	m_shapes.push_back(
		"\t<line x1=\""
		+ std::format("{:.2f}", start.x)
		+ "\" y1=\""
		+ std::format("{:.2f}", start.y)
		+ "\" x2=\""
		+ std::format("{:.2f}", end.x)
		+ "\" y2=\""
		+ std::format("{:.2f}", end.y)
		+ "\" style=\"stroke:#"
		+ color_utils::ColorToHexString(color.has_value() ? *color : 0)
		+ strokeWidth
		+ "\" />\n");
}

void CSVGCanvas::DrawPolygon(
	const std::vector<CPoint>& points,
	std::optional<std::uint32_t> outline,
	std::optional<std::uint32_t> fill)
{
	std::string pointsStr;
	for (const auto point : points)
	{
		pointsStr.append(
			std::format("{:.2f}", point.x)
			+ ","
			+ std::format("{:.2f}", point.y)
			+ " ");
	}

	m_shapes.push_back(
		"\t<polygon points=\""
		+ pointsStr
		+ "\" style=\"fill:#"
		+ color_utils::ColorToHexString(fill.has_value() ? *fill : 0xffffff)
		+ ";stroke:#"
		+ color_utils::ColorToHexString(outline.has_value() ? *outline : 0)
		+ strokeWidth
		+ "\" />\n");
}

void CSVGCanvas::DrawCircle(
	CPoint center,
	double radius,
	std::optional<std::uint32_t> outline,
	std::optional<std::uint32_t> fill)
{
	m_shapes.push_back(
		"\t<circle r=\""
		+ std::format("{:.2f}", radius)
		+ "\" cx=\""
		+ std::format("{:.2f}", center.x)
		+ "\" cy=\""
		+ std::format("{:.2f}", center.y)
		+ "\" style=\"fill:#"
		+ color_utils::ColorToHexString(fill.has_value() ? *fill : 0xffffff)
		+ ";stroke:#"
		+ color_utils::ColorToHexString(outline.has_value() ? *outline : 0)
		+ strokeWidth
		+ "\" />\n");
}