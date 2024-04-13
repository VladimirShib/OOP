#pragma once

#include "ISolidShape.h"
#include "Point.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint p1, CPoint p2, CPoint p3, std::uint32_t outline = 0, std::uint32_t fill = 0xffffff);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::uint32_t GetOutlineColor() const override;
	std::uint32_t GetFillColor() const override;
	std::string ToString() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_p1;
	CPoint m_p2;
	CPoint m_p3;
	std::uint32_t m_outlineColor;
	std::uint32_t m_fillColor;
};