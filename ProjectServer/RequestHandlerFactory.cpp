#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* loginhendler = new LoginRequestHandler(*this);
    return loginhendler;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return _m_loginManager;
}
