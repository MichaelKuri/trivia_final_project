#pragma once
#include <string>

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestion;
	unsigned int timePerQuestion;
	unsigned int isActive;

};