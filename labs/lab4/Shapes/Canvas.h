#pragma once

#include "ICanvas.h"
#include <string>
#include <vector>

class CCanvas : public ICanvas
{
public:
	bool Render() const override;
	bool Clear() override;
	void DrawLine(CPoint start, CPoint end, std::uint32_t color = 0);
	void DrawPolygon(
		const std::vector<CPoint>& points,
		std::uint32_t outline = 0,
		std::uint32_t fill = 0xffffff) override;
	void DrawCircle(
		CPoint center,
		double radius,
		std::uint32_t outline = 0,
		std::uint32_t fill = 0xffffff) override;

private:
	std::vector<std::string> m_shapes;
};