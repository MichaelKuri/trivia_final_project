#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& factory) : _m_handlerFactory(factory) {};
	virtual bool isRequestRelevant(RequestInfo) override;
	virtual RequestResult handleRequest(RequestInfo) override;

private:
	RequestHandlerFactory& _m_handlerFactory;
	RequestResult login(RequestInfo);
	RequestResult signup(RequestInfo);
};