#include "Rectangle.h"
#include "Color.h"
#include <format>
#include <vector>

CRectangle::CRectangle(CPoint topLeft, double width, double height, std::uint32_t outline, std::uint32_t fill)
	: m_topLeft(topLeft)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outline)
	, m_fillColor(fill)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) * 2;
}

std::uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

std::string CRectangle::ToString() const
{
	return "Rectangle\nPerimeter: "
		+ std::format("{:.2f}", GetPerimeter())
		+ "\nArea: "
		+ std::format("{:.2f}", GetArea())
		+ "\nOutline color: "
		+ color_utils::ColorToHexString(m_outlineColor)
		+ "\nFill color: "
		+ color_utils::ColorToHexString(m_fillColor);
}

CPoint CRectangle::GetTopLeft() const
{
	return m_topLeft;
}

CPoint CRectangle::GetBottomRight() const
{
	return { m_topLeft.x + m_width, m_topLeft.y + m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {
		m_topLeft,
		{ m_topLeft.x + m_width, m_topLeft.y },
		{ m_topLeft.x + m_width, m_topLeft.y + m_height },
		{ m_topLeft.x, m_topLeft.y + m_height }
	};

	canvas.DrawPolygon(points, m_outlineColor, m_fillColor);
}