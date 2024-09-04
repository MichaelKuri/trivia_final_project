#pragma once
#include "IRequestHandler.h"
<<<<<<< Updated upstream
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	~MenuRequestHandler();
=======
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler
{
public:

	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);
>>>>>>> Stashed changes

private:

};
