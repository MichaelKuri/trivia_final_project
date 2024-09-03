#pragma once
#include <vector>
#include <string>
struct getHighScoreResponse
{
	unsigned int _status;
	std::vector<std::string> statistics;
};