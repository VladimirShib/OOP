#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<double> ReadInputNumbers(std::istream& input);
void MultiplyVectorByMinElement(std::vector<double>& numbers);
void SortVector(std::vector<double>& numbers);
void PrintVector(std::ostream& output, const std::vector<double>& numbers);