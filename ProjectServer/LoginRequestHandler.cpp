#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo)
{
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo)
{
    return RequestResult();
}

RequestResult LoginRequestHandler::login(RequestInfo)
{
    return RequestResult();
}

RequestResult LoginRequestHandler::signup(RequestInfo)
{
    return RequestResult();
}
