#pragma once

#include "ISolidShape.h"
#include "Point.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(
		CPoint topLeft,
		double width,
		double height,
		std::uint32_t outline = 0,
		std::uint32_t fill = 0xffffff);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::uint32_t GetOutlineColor() const override;
	std::uint32_t GetFillColor() const override;
	std::string ToString() const override;
	CPoint GetTopLeft() const;
	CPoint GetBottomRight() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_topLeft;
	double m_width;
	double m_height;
	std::uint32_t m_outlineColor;
	std::uint32_t m_fillColor;
};