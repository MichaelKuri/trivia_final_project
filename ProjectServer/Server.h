#pragma once
#include "IDatabase.h"
#include "Communicator.h"
class Server
{
public:
	Server();
	~Server();
	void run();

private:

	Communicator m_communicator;
	IDatabase m_database;
	//RequestHendlerFcatory m_haendlerFactory;
};
