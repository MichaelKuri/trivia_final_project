#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler
{
public:

	bool isRequestRelevant(RequestInfo);
	RequestResult handleRequest(RequestInfo);

private:

};
