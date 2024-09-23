#include "RoomManager.h"
#include <algorithm>
#include <iterator>

void RoomManager::createRoom(LoggedUser newUser, RoomData data)
{
	Room newRoom(data);
	newRoom.addUser(newUser);
	m_rooms[data.id] = newRoom;
}

void RoomManager::deleteRoom(const unsigned int& ID)
{
	m_rooms.erase(ID);
}

unsigned int RoomManager::getRoomState(const unsigned int& ID)
{
	return m_rooms[ID].getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> allRommsData;

	std::for_each(m_rooms.begin(), m_rooms.end(), [&allRommsData](std::pair<unsigned int, Room> r) {allRommsData.push_back(r.second.getRoomData()); });
	return allRommsData;
}

Room& RoomManager::getRoom(int ID)
{
	return m_rooms[ID];
}


std::vector<Room> RoomManager::getRoomsStructs()
{
	std::vector<Room> allRomms;

	for ( auto itr = m_rooms.begin(); itr != m_rooms.end(); itr++)
	{
		allRomms.push_back(itr->second);
	}
	return allRomms;
}