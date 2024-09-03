#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* loginhendler = new LoginRequestHandler(*this);
    return loginhendler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
    return nullptr;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return _m_loginManager;
}
