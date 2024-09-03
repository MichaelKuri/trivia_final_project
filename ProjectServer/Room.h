#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>

class Room
{
public:
	Room();
	~Room();

	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	std::vector<LoggedUser> getAllUsers();


private:

	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};

