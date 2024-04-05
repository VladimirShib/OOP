#pragma once

#include "IShape.h"
#include "Point.h"
#include <memory>
#include <vector>

class CShapeCreator
{
public:
	void CreateLine(CPoint start, CPoint end, std::uint32_t color = 0);
	void CreateTriangle(CPoint p1, CPoint p2, CPoint p3, std::uint32_t outline = 0, std::uint32_t fill = 0xffffff);
	void CreateRectangle(CPoint topLeft, double width, double height, std::uint32_t outline = 0, std::uint32_t fill = 0xffffff);
	void CreateCircle(CPoint center, double radius, std::uint32_t outline = 0, std::uint32_t fill = 0xffffff);
	const std::vector<std::unique_ptr<IShape>>& GetShapes() const;
	void DeleteShapes();

private:
	std::vector<std::unique_ptr<IShape>> m_shapes;
};