#pragma once
#include <vector>
#include <string>

struct GetRoomStateResponse
{
	unsigned int _status;
	bool _hasGameBegun;
	unsigned int _questionCount;
	std::vector<std::string> _players;
	unsigned int answerTimeOut;
};

