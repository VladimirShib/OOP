#pragma once

#include <cstdint>
#include <format>
#include <string>

namespace color_utils
{

std::string ColorToHexString(std::uint32_t color);

std::string ColorToRGBstring(std::uint32_t color);

} // namespace color_utils