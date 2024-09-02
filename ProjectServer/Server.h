#pragma once
#include "SqliteDataBase.h"
#include "Communicator.h"
class Server
{
public:
	Server();
	~Server();
	void run();

private:

	Communicator m_communicator;
	SqliteDataBase m_database;
	//RequestHendlerFcatory m_haendlerFactory;
};
