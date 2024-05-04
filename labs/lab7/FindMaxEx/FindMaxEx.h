#pragma once

#include <vector>

template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto itMax = arr.begin();
	for (auto it = arr.begin() + 1; it != arr.end(); ++it)
	{
		if (less(*itMax, *it))
		{
			itMax = it;
		}
	}

	maxValue = *itMax;

	return true;
}