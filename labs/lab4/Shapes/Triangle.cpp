#include "Triangle.h"
#include "Color.h"
#include "Line.h"
#include <cmath>
#include <format>
#include <vector>

CTriangle::CTriangle(CPoint p1, CPoint p2, CPoint p3, std::uint32_t outline, std::uint32_t fill)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
	, m_outlineColor(outline)
	, m_fillColor(fill)
{
}

double CTriangle::GetArea() const
{
	double a = CLine(m_p1, m_p2).GetPerimeter();
	double b = CLine(m_p2, m_p3).GetPerimeter();
	double c = CLine(m_p3, m_p1).GetPerimeter();

	double p = (a + b + c) / 2;

	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	CLine line1(m_p1, m_p2);
	CLine line2(m_p2, m_p3);
	CLine line3(m_p3, m_p1);

	return line1.GetPerimeter() + line2.GetPerimeter() + line3.GetPerimeter();
}

std::uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CTriangle::ToString() const
{
	return "Triangle\nPerimeter: "
		+ std::format("{:.2f}", GetPerimeter())
		+ "\nArea: "
		+ std::format("{:.2f}", GetArea())
		+ "\nOutline color: "
		+ color_utils::ColorToHexString(m_outlineColor)
		+ "\nFill color: "
		+ color_utils::ColorToHexString(m_fillColor);
}

CPoint CTriangle::GetVertex1() const
{
	return m_p1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_p2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_p3;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = { m_p1, m_p2, m_p3 };

	canvas.DrawPolygon(points, m_outlineColor, m_fillColor);
}