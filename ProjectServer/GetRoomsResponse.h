#pragma once
#include <vector>
#include "RoomData.h"

struct GetRoomsResponse
{
	unsigned int _status;
	std::vector<RoomData> rooms;
};