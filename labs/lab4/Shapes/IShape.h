#pragma once

#include "ICanvas.h"
#include <cstdint>
#include <string>

class IShape
{
public:
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::uint32_t GetOutlineColor() const = 0;
	virtual std::string ToString() const = 0;
	virtual void Draw(ICanvas& canvas) const = 0;
};