#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#include <SDKDDKVer.h>

// Include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <tchar.h>

// TODO: reference additional headers your program requires here

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iomanip>

// Function definitions

std::vector<double> ReadInputNumbers(std::istream& input);
void MultiplyVectorByMinElement(std::vector<double>& numbers);
void SortAndPrintVector(std::ostream& output, std::vector<double>& numbers);