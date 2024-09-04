#pragma once
#include <map>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"
#include "Room.h"


class RoomManager
{
public:
	RoomManager();
	~RoomManager();
	void createRoom(LoggedUser, RoomData);
	void deleteRoom(const unsigned int& ID);
	unsigned int getRoomState(const unsigned int& ID);
	std::vector<RoomData> getRooms();
	Room& getroom(int ID);

private:
	unsigned int roomID;
	std::map<unsigned int, Room> m_rooms;
};
