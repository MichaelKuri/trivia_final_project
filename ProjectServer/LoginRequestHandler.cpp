#include "LoginRequestHandler.h"
#include "LoginRequest.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginResponse.h"
#include "JsonResponsePacketSerializer.h"
#include "triviaProtocol.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo rinfo)
{
    return (rinfo.id == SIGNOUT || rinfo.id == LOGIN);
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

//TO DO - hendle exeptions 
RequestResult LoginRequestHandler::login(RequestInfo rinfo )
{
    RequestResult rResult;
    LoginRequest logReq = JsonRequestPacketDeserializer::deserializeLoginRequest(rinfo.Buffer);
    bool loginChecked = this->m_handlerFactory.getLoginManager().login(logReq.username, logReq.password);

    if (loginChecked)
    {
        rResult.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(logReq.username));
        LoginResponse lr;
        lr._status = SUCSESS;
        rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
    }
    else
    {
        LoginResponse lr;
        lr._status = FAILD;
        rResult.newHandler = m_handlerFactory.createLoginRequestHandler();
        rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
    }
    return rResult;
}

//TO DO - hendle exeptions 
RequestResult LoginRequestHandler::signup(RequestInfo rinfo)
{
    RequestResult rResult;
    SignupRequest logReq = JsonRequestPacketDeserializer::deserializeSignupRequest(rinfo.Buffer);
    bool loginChecked = this->m_handlerFactory.getLoginManager().signup(logReq.username, logReq.password, logReq.email);

    if (loginChecked)
    {
        LoginResponse lr;
        lr._status = SUCSESS;
        rResult.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(logReq.username));
        rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
    }
    else
    {
        LoginResponse lr;
        lr._status = FAILD;
        rResult.newHandler = m_handlerFactory.createLoginRequestHandler();
        rResult.response = JsonResponsePacketSerializer::SerializeResponse(lr);
    }
    return rResult;
}
