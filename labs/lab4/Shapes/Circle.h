#pragma once

#include "ISolidShape.h"
#include "Point.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius, std::uint32_t outline = 0, std::uint32_t fill = 0xff);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::uint32_t GetOutlineColor() const override;
	std::uint32_t GetFillColor() const override;
	std::string ToString() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_center;
	double m_radius;
	std::uint32_t m_outlineColor;
	std::uint32_t m_fillColor;
};