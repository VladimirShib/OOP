#include "Circle.h"
#include "Color.h"
#include <cmath>
#include <format>
#include <numbers>

CCircle::CCircle(CPoint center, double radius, std::uint32_t outline, std::uint32_t fill)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outline)
	, m_fillColor(fill)
{
}

double CCircle::GetArea() const
{
	return std::numbers::pi * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * std::numbers::pi * m_radius;
}

std::uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

std::string CCircle::ToString() const
{
	return "Circle\nCircumference: "
		+ std::format("{:.2f}", GetPerimeter())
		+ "\nArea: "
		+ std::format("{:.2f}", GetArea())
		+ "\nOutline color: "
		+ color_utils::ColorToHexString(m_outlineColor)
		+ "\nFill color: "
		+ color_utils::ColorToHexString(m_fillColor);
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_center, m_radius, m_outlineColor, m_fillColor);
}