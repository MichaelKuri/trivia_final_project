#pragma once

#include "MagshChat.h"
#include <map>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <WinSock2.h>
#include "RecvMessage.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"


// Q: why do we need this class ?
// A: this is the main class which holds all the resources,
// accept new clients and handle them.
class Communicator
{
public:
	Communicator(RequestHandlerFactory& factory);
	~Communicator();
	void serve();
	void startHandleRequests();

private:

	void bindAndListen();
	void handleNewClient(const SOCKET client_socket);
	//void safeDeleteUser(const SOCKET id);
	//BONUS
	//-m_cryptoAlgorithm : ICryptoAlgorithm
	//void handleReceivedMessages();
	//std::string getCurrentUser();
	//std::string getNextUser();
	//std::string get_user_name(const SOCKET id);
	//void addReceivedMessage(RecvMessage*);
	//static RecvMessage* build_receive_message(const SOCKET client_socket, const int msg_code);
	//std::string getAllUsernames();
		

	std::map<SOCKET, IRequestHandler*> _m_clients;
	RequestHandlerFactory& _m_handlerFactory;

	SOCKET _m_serverSocket;

	//TO do check mutex
	std::mutex _mtxReceivedMessages;
	std::condition_variable _msgQueueCondition;
};

