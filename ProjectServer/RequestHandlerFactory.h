#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;
class LoginManager;
class MenuRequestHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database) : _m_database(database), _m_loginManager(database){};
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
	MenuRequestHandler* createMenuRequestHandler();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

private:
	LoginManager _m_loginManager;
	IDatabase* _m_database;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager

};

