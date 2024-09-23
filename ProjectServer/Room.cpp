#include "Room.h"



Room::Room()
{
}

void Room::addUser(LoggedUser user)
{
	if (m_users.size() >= m_metadata.maxPlayers)
	{
		return;
	}
	m_users.push_back(user);
}


void Room::removeUser(LoggedUser user)
{
	for (auto i = m_users.begin(); i != m_users.end(); i++)
	{
		if (i->getUsername() == user.getUsername())
		{
			m_users.erase(i);
		}
	}
}


std::vector<LoggedUser> Room::getAllUsers()
{
	return m_users;
}

RoomData Room::getRoomData()
{
	return m_metadata;
}

