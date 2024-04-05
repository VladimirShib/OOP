#pragma once

#include "Point.h"
#include <cstdint>
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual bool Render() const = 0;
	virtual bool Clear() = 0;
	virtual void DrawLine(CPoint start, CPoint end, std::uint32_t color) = 0;
	virtual void DrawPolygon(const std::vector<CPoint>& points, std::uint32_t outline, std::uint32_t fill) = 0;
	virtual void DrawCircle(CPoint center, double radius, std::uint32_t outline, std::uint32_t fill) = 0;
};