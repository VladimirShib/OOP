#pragma once

#include "IShape.h"
#include "Point.h"

class CLine : public IShape
{
public:
	CLine(CPoint startPoint, CPoint endPoint, std::uint32_t color = 0);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::uint32_t GetOutlineColor() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	std::uint32_t m_outlineColor;
};