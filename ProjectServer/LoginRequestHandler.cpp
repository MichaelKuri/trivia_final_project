#include "LoginRequestHandler.h"
#include "LoginRequest.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginResponse.h"
#include "JsonResponsePacketSerializer.h"

#define OK 200
#define INCORRECT 201
bool LoginRequestHandler::isRequestRelevant(RequestInfo rinfo)
{
	return (rinfo.id == 1 || rinfo.id == 2 || rinfo.id == 3);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo ri)
{
	RequestResult rr;
	if (ri.id == 1)
	{
		rr = login(ri);
	}
	else
	{
		rr = signup(ri);
	}

	return rr;
}

RequestResult LoginRequestHandler::login(RequestInfo rinfo )
{
	RequestResult rResult;
	LoginRequest logReq = JsonRequestPacketDeserializer::deserializeLoginRequest(rinfo.Buffer);
	bool loginChecked = this->_m_handlerFactory.getLoginManager().login(logReq.username, logReq.password);
	if (loginChecked)
	{
		rResult.newHandler = _m_handlerFactory.createMenuRequestHandler();
		LoginResponse lr;
		lr._status = OK;
		rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
	}
	else
	{
		LoginResponse lr;
		lr._status = INCORRECT;
		rResult.newHandler = _m_handlerFactory.createLoginRequestHandler();
		rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
	}
	return rResult;
}

RequestResult LoginRequestHandler::signup(RequestInfo rinfo)
{
	RequestResult rResult;
	SignupRequest logReq = JsonRequestPacketDeserializer::deserializeSignupRequest(rinfo.Buffer);
	bool loginChecked = this->_m_handlerFactory.getLoginManager().signup(logReq.username, logReq.password, logReq.email);
	if (loginChecked)
	{
		LoginResponse lr;
		lr._status = OK;
		rResult.newHandler = _m_handlerFactory.createMenuRequestHandler();
		rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
	}
	else
	{
		LoginResponse lr;
		lr._status = INCORRECT;
		rResult.newHandler = _m_handlerFactory.createLoginRequestHandler();
		rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
	}
	return rResult;
}
