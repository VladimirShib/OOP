#pragma once

#include <iostream>
#include <string>

struct URL
{
	std::string fullUrl;
	std::string host;
	int port;
	std::string document;
};

bool ParseUrl(URL& url, const std::string& str);
void PrintUrl(std::ostream& output, const URL& url);