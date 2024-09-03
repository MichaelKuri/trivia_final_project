
#include "Communicator.h"
#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <ctime>
#include "LoginRequestHandler.h"
#include "Helper.h"
#include "ErrorResponse.h"
#include "JsonResponsePacketSerializer.h"

// using static const instead of macros 
static const unsigned short PORT = 8826;
static const unsigned int IFACE = 0;

using std::string;
using std::mutex;
using std::unique_lock;
using std::vector;


Communicator::Communicator(RequestHandlerFactory& factory) : _m_handlerFactory(factory)
{
	// notice that we step out to the global namespace
	// for the resolution of the function socket
	_m_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_m_serverSocket == INVALID_SOCKET)
		throw std::exception( __FUNCTION__ " - socket");

	//restart factory
}

Communicator::~Communicator()
{
	TRACE(__FUNCTION__ " closing accepting socket");
	// why is this try necessarily ?
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		::closesocket(_m_serverSocket);
	}
	catch (...) {}
}

void Communicator::serve()
{
	bindAndListen();


	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		TRACE("accepting client...");
		startHandleRequests();
	}
}


// listen to connecting requests from clients
// accept them, and create thread for each client
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	// again stepping out to the global namespace
	if (::bind(_m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	TRACE("binded");

	if (::listen(_m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	TRACE("listening...");
}

void Communicator::startHandleRequests()
{
	SOCKET client_socket = accept(_m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	TRACE("Client accepted !");
	


	_m_clients[client_socket] = _m_handlerFactory.createLoginRequestHandler();



	//create new thread for client	and detach from it
	std::thread tr(&Communicator::handleNewClient, this, client_socket);
	tr.detach();

}



void Communicator::handleNewClient(const SOCKET client_socket)
{
	
	RequestInfo rinfo;

	while (true)
	{
		char code[1];
		recv(client_socket, code, 1, 0);
		int msgCode = (int)(code[0]);

		if (msgCode == 0)
		{
			std::cout << "Error: can't reading from user";
			closesocket(client_socket);
			return;
		}
		
		rinfo.id = msgCode;



		//createloginrequesthendler()



		//get len msg from buffer n convert message len to int  //needs to check!!!!!
		//int msgLen = Helper::getIntPartFromSocket(client_socket, 4);
		char lenField[4];
		recv(client_socket, lenField, 4, 0);
		unsigned int msgLen = 0;
		for (size_t i = 0; i < 4; i++)
		{
			msgLen = msgLen << 8;
			msgLen = msgLen ^ lenField[i];
		}


		char* msgData = new char[msgLen];
		recv(client_socket, msgData, msgLen, 0);
		//msgData = Helper::getStringPartFromSocket(client_socket, msgLen);

		for (int i = 0; i < msgLen; i++)
		{
			rinfo.Buffer.push_back(msgData[i]);
		}

		//rinfo.receivalTime = 
		//rinfo.time



		//if isrequestrelevant(rinfo)
		if (!(this->_m_clients[client_socket]->isRequestRelevant(rinfo)))
		{
			ErrorResponse error;
			std::string errMsg;
			error.message = "irelvant code";
			std::vector<char> errorRes = JsonResponsePacketSerializer::SerializeResponse(error);
			for (size_t i = 0; i < errorRes.size(); i++)
			{
				errMsg += errorRes[i];
			}

			send(client_socket, errMsg.c_str(), errMsg.size(), 0);
			return;
		}
		else 
		{
			RequestResult rr = this->_m_clients[client_socket]->handleRequest(rinfo);
			delete _m_clients[client_socket];
			_m_clients[client_socket] = rr.newHandler;
			std::string strSend;
			for (size_t i = 0; i < rr.response.size(); i++)
			{
				strSend += rr.response[i];
			}
			send(client_socket, strSend.c_str(), strSend.size(), 0);
		}

	}
	

	
	int code = Helper::getMessageTypeCode(client_socket);
	std::cout << code << std::endl;

	closesocket(client_socket);
}


