#include "RoomMemberRequestHandler.h"
#include "triviaProtocol.h"

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo ri)
{
	if (ri.id == GET_ROOM_STATE || ri.id == LEAVE_ROOM )
	{
		return true;
	}
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo)
{
    return RequestResult();
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo)
{
    return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo)
{
    return RequestResult();
}
