#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include <iostream>
class MenuRequestHandler : public IRequestHandler
{
public:

	//	MenuRequestHandler(RequestHandlerFactory& factory, LoggedUser& lu);

	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);


private:
	LoggedUser m_user;
	RequestHandlerFactory& m_handleFactory;

	RequestResult signout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getPersonalStats(RequestInfo);
	RequestResult getHighScore(RequestInfo);
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);

};
