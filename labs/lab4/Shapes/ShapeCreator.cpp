#include "ShapeCreator.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include "Triangle.h"

void CShapeCreator::CreateLine(CPoint start, CPoint end, std::uint32_t color)
{
	m_shapes.push_back(std::make_unique<CLine>(start, end, color));
}

void CShapeCreator::CreateTriangle(CPoint p1, CPoint p2, CPoint p3, std::uint32_t outline, std::uint32_t fill)
{
	m_shapes.push_back(std::make_unique<CTriangle>(p1, p2, p3, outline, fill));
}

void CShapeCreator::CreateRectangle(
	CPoint topLeft,
	double width,
	double height,
	std::uint32_t outline,
	std::uint32_t fill)
{
	m_shapes.push_back(std::make_unique<CRectangle>(topLeft, width, height, outline, fill));
}

void CShapeCreator::CreateCircle(CPoint center, double radius, std::uint32_t outline, std::uint32_t fill)
{
	m_shapes.push_back(std::make_unique<CCircle>(center, radius, outline, fill));
}

const std::vector<std::unique_ptr<IShape>>& CShapeCreator::GetShapes() const
{
	return m_shapes;
}

void CShapeCreator::DeleteShapes()
{
	m_shapes.clear();
}