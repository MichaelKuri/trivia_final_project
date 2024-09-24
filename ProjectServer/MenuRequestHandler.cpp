#include "MenuRequestHandler.h"
#include "CreateRoomRequest.h"
#include "CreateRoomResponse.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "triviaProtocol.h"



bool MenuRequestHandler::isRequestRelevant(RequestInfo ri)
{
	if (ri.id > 2 || ri.id < 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}


RequestResult MenuRequestHandler::handleRequest(RequestInfo ri)
{
	RequestResult res;
	unsigned int num;
	std::vector<RoomData> rooms;

	if (this->isRequestRelevant(ri))
	{
		switch (ri.id)//msgCode
		{
		case 4:
			res = this->createRoom(ri);
			break;
		case 6:	//join room
			res = this->joinRoom(ri);
			break;
		case 7:
			res = this->getRooms(ri);
			break;
			 //user gives back roomID and we need to connect'em to this room
			break;
		case 8:
			res = this->signout(ri);

		default:
			break;
		}

	}
	return res;
}


RequestResult MenuRequestHandler::signout(RequestInfo ri)
{
	LogoutResponse logoutRes;
	logoutRes._status = 999;
	RequestResult res;
	std::string name = this->m_user.getUsername();
	this->m_handleFactory.getLoginManager().logout(name);
	std::vector<Room> rooms = this->m_handleFactory.getRoomManager().getRoomsStructs();
	for (auto i = rooms.begin();  i != rooms.end();  i++)
	{
		std::vector<LoggedUser> users = i->getAllUsers();
		for (auto itr = users.begin(); itr != users.end(); i++)
		{
			if (itr->getUsername() == m_user.getUsername())
			{
				i->removeUser(m_user);
			}
		}
			
	}
	res.response = JsonResponsePacketSerializer::SerializeResponse(logoutRes);
	res.newHandler = m_handleFactory.createLoginRequestHandler();
	return res;

}


RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo ri)
{

	RequestResult res;
	GetPlayersInRoomRequest getPlayers = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(ri.Buffer);
	Room currentRoom = this->m_handleFactory.getRoomManager().getRoom(getPlayers.roomId);
	GetPlayersInRoomResponse getplayerRes;
	std::vector<LoggedUser> allPlayers = currentRoom.getAllUsers() ;
	std::for_each(allPlayers.begin(), allPlayers.end(), [&getplayerRes](auto user) { getplayerRes.players.push_back(user.getUsername()); });
	res.response = JsonResponsePacketSerializer::SerializeResponse(getplayerRes);
	res.newHandler = this;
	return res;
}



RequestResult MenuRequestHandler::getPersonalStats(RequestInfo ri)
{
	RequestResult res;
	std::string name = m_user.getUsername();
	std::vector<std::string> personalStats = this->m_handleFactory.getStatisticsManager().getUserStatistics(name);
	getPersonalStatsResponse getpersonalStat;
	res.response = JsonResponsePacketSerializer::SerializeResponse(getpersonalStat);
	res.newHandler = this;
	return res;
}


RequestResult MenuRequestHandler::getHighScore(RequestInfo ri)
{
	RequestResult res;
	std::vector<std::string> personalStats = this->m_handleFactory.getStatisticsManager().getHighScore();
	getHighScoreResponse gethighScore;
	res.response = JsonResponsePacketSerializer::SerializeResponse(gethighScore);
	res.newHandler = this;
	return res;
}


RequestResult MenuRequestHandler::getRooms(RequestInfo)
{
	RequestResult res;
	GetRoomsResponse getroomRes;
	std::vector<RoomData> rooms = this->m_handleFactory.getRoomManager().getRooms();
	getroomRes._status = 200;
	getroomRes.rooms = rooms;
	res.response = JsonResponsePacketSerializer::SerializeResponse(getroomRes);
	res.newHandler = this;
	return res;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo ri)
{
	RequestResult res;
	JoinRoomResponse joinroomRes;
	JoinRoomRequest joinRoomReq = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(ri.Buffer);
	Room  room = this->m_handleFactory.getRoomManager().getRoom(joinRoomReq.roomId);
	room.addUser(this->m_user);
	joinroomRes._status = 200;
	res.response = JsonResponsePacketSerializer::SerializeResponse(joinroomRes);
	res.newHandler = this;
	return res;
}


RequestResult MenuRequestHandler::createRoom(RequestInfo ri)
{

	CreateRoomRequest createRoomReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(ri.Buffer);

	RoomData rData;
	RequestResult res;
	CreateRoomResponse createRoomRes;
	rData.name = createRoomReq.roomName;
	rData.maxPlayers = createRoomReq.maxUsers;
	rData.numOfQuestion = createRoomReq.questionCount;
	rData.timePerQuestion = createRoomReq.answerTimeout;
	rData.id = (unsigned int)rData.name[0] * rData.numOfQuestion * 123;
	this->m_handleFactory.getRoomManager().createRoom(this->m_user, rData);
	createRoomRes._status = 200;
	res.response = JsonResponsePacketSerializer::SerializeResponse(createRoomRes);
	res.newHandler = this;
	return res;
}



