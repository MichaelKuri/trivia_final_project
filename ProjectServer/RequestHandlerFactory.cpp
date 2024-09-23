#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    LoginRequestHandler* loginhendler = new LoginRequestHandler(*this);
    return loginhendler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser)
{

    return nullptr;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return _m_loginManager;
}


StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return this->m_statisticsManager;
}


RoomManager& RequestHandlerFactory::getRoomManager()
{
    return this->m_roomManager;
}
