#pragma once
#include "IRequestHandler.h"
#include <vector>

class IRequestHandler;

struct RequestResult
{
	IRequestHandler* newHandler;
	std::vector<char> response;
};