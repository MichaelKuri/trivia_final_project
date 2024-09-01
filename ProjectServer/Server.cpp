
#include "Server.h"

Server::Server()
{
}

Server::~Server()
{
}

void Server::run()
{
	m_communicator.serve();

}
