
#include "Server.h"

Server::Server(IDatabase* database ) : m_database(database), m_haendlerFactory(m_database), m_communicator(m_haendlerFactory)
{

}

Server::~Server()
{
}

void Server::run()
{
	m_communicator.serve();

}
