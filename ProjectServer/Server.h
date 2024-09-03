#pragma once
#include "SqliteDataBase.h"
#include "Communicator.h"
#include "RequestHandlerFactory.h"

class Server
{
public:
	Server(IDatabase* database);
	~Server();
	void run();
private:
	Communicator m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_haendlerFactory;
};
