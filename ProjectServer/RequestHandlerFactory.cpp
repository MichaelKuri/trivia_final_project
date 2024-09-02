#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler(*this);
    return nullptr;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return _m_loginManager;
}
