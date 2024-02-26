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

#include <regex>
#include <algorithm>
#include <locale>

// Function declarations

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21
};

struct URL
{
	std::string fullUrl;
	std::string host;
	int port;
	std::string document;
};

bool ParseUrl(URL& url, const std::string& str);
bool SaveData(URL& url, const std::smatch& result);
bool GetProtocol(std::string result, std::string& protocol);
int GetDefaultPort(const std::string& protocol);
void PrintUrl(std::ostream& output, const URL& url);