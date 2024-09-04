#include "MenuRequestHandler.h"
#include "CreateRoomRequest.h"
#include "CreateRoomResponse.h"
#include "JsonRequestPacketDeserializer.h"




bool MenuRequestHandler::isRequestRelevant(RequestInfo ri)
{
	if (ri.id == 8)
	{
		this->signout(ri);
	}
	else if (ri.id > 2 || ri.id < 8)
	{
		return true;
	}
}


RequestResult MenuRequestHandler::handleRequest(RequestInfo ri)
{
	unsigned int num;
	std::vector<RoomData> rooms;

	if (this->isRequestRelevant(ri))
	{
		switch (ri.id)//msgCode
		{
		case 3:
			//send menu
			break;
		case 4:
			this->createRoom(ri);
			break;
		case 5:
			//needs to change to talk with user/buffer
			std::cout << "enter room ID: ";
			std::cin >> num;
			this->m_handleFactory.getRoomManager().deleteRoom(num);
			//needs to send to user/buffer
			break;

		case 6:	//join room
			 rooms = this->m_handleFactory.getRoomManager().getRooms();
			//needs to send  'rooms' to user/buffer

			 //user gives back roomID and we need to connect'em to this room

			break;

		default:
			break;
		}
		
	}

}


RequestResult MenuRequestHandler::signout(RequestInfo ri)
{
	//delete user 

}


RequestResult MenuRequestHandler::getRooms(RequestInfo ri)
{


}


RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo ri)
{


}


RequestResult MenuRequestHandler::getPersonalStats(RequestInfo ri)
{


}


RequestResult MenuRequestHandler::getHighScore(RequestInfo ri)
{


}


RequestResult MenuRequestHandler::joinRoom(RequestInfo ri)
{


}


RequestResult MenuRequestHandler::createRoom(RequestInfo ri)
{

	CreateRoomRequest createRoomReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(ri.Buffer);
	
	RoomData rData;
	rData.name = createRoomReq.roomName;
	rData.maxPlayers = createRoomReq.maxUsers;
	rData.numOfQuestion = createRoomReq.questionCount;
	rData.timePerQuestion = createRoomReq.answerTimeout;
	rData.id = (unsigned int)rData.name[0] * rData.numOfQuestion * 123;
	this->m_handleFactory.getRoomManager().createRoom(this->m_user, rData);
	RequestResult res;
	res.newHandler = 

}




