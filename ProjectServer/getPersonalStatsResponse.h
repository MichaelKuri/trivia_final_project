#pragma once
#include <vector>
#include <string>
struct getPersonalStatsResponse
{
	unsigned int _status;
	std::vector<std::string> statistics;
};