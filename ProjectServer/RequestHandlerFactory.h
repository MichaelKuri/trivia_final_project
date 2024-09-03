#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
//#include "RoomManager.h"
class LoginRequestHandler;
class LoginManager;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database) : _m_database(database), _m_loginManager(database){};
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager _m_loginManager;
	IDatabase* _m_database;

	//RoomManager 

};

