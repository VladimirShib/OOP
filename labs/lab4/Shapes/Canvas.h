#pragma once

#include "ICanvas.h"

class CSVGCanvas : public ICanvas
{
public:
	bool RenderToFile(const std::string& fileName);
	bool Clear(const std::string& fileName);
	void DrawLine(CPoint start, CPoint end, std::optional<std::uint32_t> color = std::nullopt);
	void DrawPolygon(
		const std::vector<CPoint>& points,
		std::optional<std::uint32_t> outline = std::nullopt,
		std::optional<std::uint32_t> fill = std::nullopt) override;
	void DrawCircle(
		CPoint center,
		double radius,
		std::optional<std::uint32_t> outline = std::nullopt,
		std::optional<std::uint32_t> fill = std::nullopt) override;

private:
	std::vector<std::string> m_shapes;
};