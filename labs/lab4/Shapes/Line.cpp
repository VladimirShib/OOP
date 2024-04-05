#include "Line.h"
#include "Color.h"
#include <cmath>
#include <format>

CLine::CLine(CPoint startPoint, CPoint endPoint, std::uint32_t color)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(color)
{
}

double CLine::GetArea() const
{
	return 0.0;
}

double CLine::GetPerimeter() const
{
	return std::sqrt(std::pow(m_startPoint.x - m_endPoint.x, 2) + std::pow(m_startPoint.y - m_endPoint.y, 2));
}

std::uint32_t CLine::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CLine::ToString() const
{
	return "Line\nLength: "
		+ std::format("{:.2f}", GetPerimeter())
		+ "\nArea: 0\n"
		+ "Color: "
		+ color_utils::ColorToHexString(m_outlineColor);
}

CPoint CLine::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLine::GetEndPoint() const
{
	return m_endPoint;
}

void CLine::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}