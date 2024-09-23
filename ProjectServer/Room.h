#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>

class Room
{
public:
	Room();
	Room(RoomData data) { m_metadata = data; };
	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	std::vector<LoggedUser> getAllUsers();
	RoomData getRoomData();


private:

	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

