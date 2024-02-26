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
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <tchar.h>

// TODO: reference additional headers your program requires here

#include <sstream>
#include <locale>
#include <stack>

// Function declarations

enum class Operation
{
	ADDITION,
	MULTIPLICATION
};

int CaculateExpression(const std::string& expression);
int DoCalculations(std::istream& input);
void Init(std::istream& input, Operation& operation);
Operation GetOperation(char ch);
void ValidateChar(std::istream& input, char ch);
void CalculateResult(int& result, const int value, const Operation& operation);