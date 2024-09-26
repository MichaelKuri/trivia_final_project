#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	/**
	Constractor to loginRequestHandler 
	@param factory to init m_handlerFactory*/
	LoginRequestHandler(RequestHandlerFactory& factory) : m_handlerFactory(factory) {};

	/**
	Check if the request code is in the range of the corrent user options
	@param requestInfo the request to check
	@return true if the request relevant false otherwise
	*/
	virtual bool isRequestRelevant(RequestInfo requestInfo) override;

	/**
	Hendle the request process it and construct an response to send
	@param requestInfo the request to process
	*/
	virtual RequestResult handleRequest(RequestInfo requestInfo) override;

private:
	RequestResult login(RequestInfo);
	RequestResult signup(RequestInfo);

	// field to store refernce to the factory
	RequestHandlerFactory& m_handlerFactory;
	
};