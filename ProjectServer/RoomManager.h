#pragma once
#include <map>
#include <vector>
#include "LoggedUser.h"
#include "RoomData.h"
#include "Room.h"


class RoomManager
{
public:
	void createRoom(LoggedUser, RoomData);
	void deleteRoom(const unsigned int& ID);
	unsigned int getRoomState(const unsigned int& ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
	std::vector<Room> getRoomsStructs();
private:
	unsigned int roomID;
	std::map<unsigned int, Room> m_rooms;
};
