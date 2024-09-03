#pragma once
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() {};
	~MenuRequestHandler() {};

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
