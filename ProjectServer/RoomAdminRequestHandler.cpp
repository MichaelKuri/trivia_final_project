#include "RoomAdminRequestHandler.h"
#include "triviaProtocol.h"

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo ri)
{
	if (ri.id == CLOSE_ROOM || ri.id == START_GAME || ri.id == GET_ROOM_STATE)
	{
		return true;
	}
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo ri)
{
	RequestResult res;

	if (this->isRequestRelevant(ri))
	{
		switch (ri.id)//msgCode
		{
		case CLOSE_ROOM:
			res = this->closeRoom(ri);
			break;

		case START_GAME:
			res = this->startGame(ri);
			break;

		case GET_ROOM_STATE:	
			res = this->getRoomState(ri);
			break;

		default:
			break;
		}
	}
	return res;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo)
{
	int roomId = _m_room.getRoomData().id;
	_m_roomManager.deleteRoom(roomId);
	//TODO send to users in the room messege to leave
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo)
{
	//TODO send to users in the room messege to start a game
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo)
{
	int state = _m_room.getRoomData().isActive;
	return RequestResult();
}

