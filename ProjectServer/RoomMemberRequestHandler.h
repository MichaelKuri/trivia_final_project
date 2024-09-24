#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"


class RoomMemberRequestHandler : public IRequestHandler
{

public:
	bool isRequestRelevant(RequestInfo);
	RequestResult  handleRequest(RequestInfo);
	
private:
	RequestResult leaveRoom(RequestInfo);
	RequestResult getRoomState(RequestInfo);

	Room _m_room;
	LoggedUser _m_user;
	RoomManager& _m_roomManager;
	RequestHandlerFactory& _m_handlerFactory;

};
