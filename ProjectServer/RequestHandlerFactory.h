#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
class LoginRequestHandler;
class LoginManager;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* database) : _m_database(database), _m_loginManager(database){};
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager _m_loginManager;
	IDatabase* _m_database;

};

