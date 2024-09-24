#include "LoginRequestHandler.h"
#include "LoginRequest.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginResponse.h"
#include "JsonResponsePacketSerializer.h"
#include "triviaProtocol.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo rinfo)
{
	return (rinfo.id == 1 || rinfo.id == 2 );
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo ri)
{
	RequestResult rr;
	if (ri.id == LOGIN)
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
		rResult.newHandler = _m_handlerFactory.createMenuRequestHandler(LoggedUser(logReq.username));
		LoginResponse lr;
		lr._status = SUCSESS;
		rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
	}
	else
	{
		LoginResponse lr;
		lr._status = FAILD;
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
		lr._status = SUCSESS;
		rResult.newHandler = _m_handlerFactory.createMenuRequestHandler(LoggedUser(logReq.username));
		rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
	}
	else
	{
		LoginResponse lr;
		lr._status = FAILD;
		rResult.newHandler = _m_handlerFactory.createLoginRequestHandler();
		rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
	}
	return rResult;
}
