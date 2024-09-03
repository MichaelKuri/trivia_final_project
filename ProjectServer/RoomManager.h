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
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getroom(int ID);

private:
	//I dont know what is roomID
	//std::map<roomID, Room> m_rooms;
};
