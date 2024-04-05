#include "Color.h"

namespace color_utils
{

std::string ColorToHexString(std::uint32_t color)
{
	if (color <= 0xffffff)
	{
		std::uint8_t r = static_cast<std::uint8_t>((color & 0xff0000) >> 16);
		std::uint8_t g = static_cast<std::uint8_t>((color & 0x00ff00) >> 8);
		std::uint8_t b = static_cast<std::uint8_t>(color & 0x0000ff);

		return std::format("{:02x}{:02x}{:02x}", r, g, b);
	}

	std::uint8_t r = static_cast<std::uint8_t>((color & 0xff000000) >> 24);
	std::uint8_t g = static_cast<std::uint8_t>((color & 0x00ff0000) >> 16);
	std::uint8_t b = static_cast<std::uint8_t>((color & 0x0000ff00) >> 8);
	std::uint8_t a = static_cast<std::uint8_t>(color & 0x000000ff);

	return std::format("{:02x}{:02x}{:02x}{:02x}", r, g, b, a);
}

std::string ColorToRGBstring(std::uint32_t color)
{
	if (color <= 0xffffff)
	{
		std::uint8_t r = static_cast<std::uint8_t>((color & 0xff0000) >> 16);
		std::uint8_t g = static_cast<std::uint8_t>((color & 0x00ff00) >> 8);
		std::uint8_t b = static_cast<std::uint8_t>(color & 0x0000ff);

		return std::format("{}, {}, {}, ", r, g, b);
	}

	std::uint8_t r = static_cast<std::uint8_t>((color & 0xff000000) >> 24);
	std::uint8_t g = static_cast<std::uint8_t>((color & 0x00ff0000) >> 16);
	std::uint8_t b = static_cast<std::uint8_t>((color & 0x0000ff00) >> 8);
	std::uint8_t a = static_cast<std::uint8_t>(color & 0x000000ff);

	return std::format("{}, {}, {}, {}, ", r, g, b, a);
}

} // namespace color_utils