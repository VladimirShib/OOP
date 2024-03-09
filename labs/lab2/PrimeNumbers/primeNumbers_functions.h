#pragma once

#include <iostream>
#include <set>

std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintSet(std::ostream& output, const std::set<int>& primes);