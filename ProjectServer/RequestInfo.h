#pragma once
#include <vector>
struct RequestInfo
{
	int id;

	int receivalTime;

	std::vector<char> Buffer;
};