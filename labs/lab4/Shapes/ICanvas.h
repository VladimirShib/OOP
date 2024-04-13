#pragma once

#include "Point.h"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;

	virtual void DrawLine(CPoint start, CPoint end, std::optional<std::uint32_t> color = std::nullopt) = 0;
	virtual void DrawPolygon(
		const std::vector<CPoint>& points,
		std::optional<std::uint32_t> outline = std::nullopt,
		std::optional<std::uint32_t> fill = std::nullopt)
		= 0;
	virtual void DrawCircle(
		CPoint center,
		double radius,
		std::optional<std::uint32_t> outline = std::nullopt,
		std::optional<std::uint32_t> fill = std::nullopt)
		= 0;
};