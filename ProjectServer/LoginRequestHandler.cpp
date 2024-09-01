#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo)
{
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo)
{
    return RequestResult();
}
