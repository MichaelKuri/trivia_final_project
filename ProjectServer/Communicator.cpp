#include <exception>
#include <iostream>
#include <string>
#include <numeric>
#include <ctime>
#include "LoginRequestHandler.h"
#include "Helper.h"
#include "ErrorResponse.h"
#include "JsonResponsePacketSerializer.h"
#include "Communicator.h"

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

//TO DO sprate to multipile func to check messages
void Communicator::handleNewClient(const SOCKET client_socket)
{
    char firstmsg[7] = "hello\0";
    send(client_socket, firstmsg, 6, 0);
    int check = recv(client_socket, firstmsg, 7, 0);
    std::cout << firstmsg <<"\n";
    RequestInfo rinfo;

    try
    {
        while (true)
        {
            // acquire the mutex to ensure exclusive access to the client socket and related operations
            std::lock_guard<std::mutex> lock(_mtxReceivedMessages);

            char code[1];
            int bytesReceived = recv(client_socket, code, 1, 0);
            if (bytesReceived <= 0) 
            {
                std::cout << "Error: can't read from user or connection closed";
                closesocket(client_socket);
                return;
            }

            int msgCode = static_cast<int>(code[0]);

            assert(msgCode >= 0);

            if (msgCode == 0)
            {
                std::cout << "Error: can't read from user";
                closesocket(client_socket);
                return;
            }

            rinfo.id = msgCode;

            assert(rinfo.id >= 100);
            char lenField[4];

            bytesReceived = recv(client_socket, lenField, 4, 0);
            if (bytesReceived != 4) 
            {
                std::cout << "Error: failed to read length field";
                closesocket(client_socket);
                return;
            }

            unsigned int msgLen = 0;
            for (size_t i = 0; i < 4; i++)
            {
                msgLen = (msgLen << 8) | static_cast<unsigned char>(lenField[i]);
            }

            char* msgData = new char[msgLen];
            bytesReceived = recv(client_socket, msgData, msgLen, 0);
            if (bytesReceived != msgLen) 
            {
                std::cout << "Error: failed to read message data";
                delete[] msgData;
                closesocket(client_socket);
                return;
            }

            rinfo.Buffer.assign(msgData, msgData + msgLen);
            delete[] msgData;

            if (!(this->_m_clients[client_socket]->isRequestRelevant(rinfo)))
            {
                ErrorResponse error;
                error.message = "irrelevant code";
                std::vector<char> errorRes = JsonResponsePacketSerializer::SerializeResponse(error);
                send(client_socket, errorRes.data(), errorRes.size(), 0);
                return;
            }
            else
            {
                RequestResult rr = this->_m_clients[client_socket]->handleRequest(rinfo);
                delete _m_clients[client_socket];
                _m_clients[client_socket] = rr.newHandler;

                send(client_socket, rr.response.data(), rr.response.size(), 0);
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "exception caught: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "unknown exception caught" << std::endl;
    }

    closesocket(client_socket);
}



