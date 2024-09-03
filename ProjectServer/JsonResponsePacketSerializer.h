#pragma once
#include <vector>
#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "LogoutResponse.h"
#include "GetRoomsResponse.h"
#include "GetPlayersInRoomResponse.h"
#include "JoinRoomResponse.h"
#include "CreateRoomResponse.h"
#include "getHighScoreResponse.h"
#include "getPersonalStatsResponse.h"
#include <vector>
#include <cstring>
#include "json.hpp"

using json = nlohmann::json;


class JsonResponsePacketSerializer
{
public:


	static std::vector<char> SerializeResponse(const ErrorResponse& response);
	static std::vector<char> SerializeResponse(const LoginResponse& response);
	static std::vector<char> SerializeResponse(const SignupResponse& response);
	static std::vector<char> ConvertJsonToBuffer(const json& j);
	
	static std::vector<char> SerializeResponse(const LogoutResponse& response);
	static std::vector<char> SerializeResponse(const GetRoomsResponse& response);
	static std::vector<char> SerializeResponse(const GetPlayersInRoomResponse& response);
	static std::vector<char> SerializeResponse(const JoinRoomResponse& response);
	static std::vector<char> SerializeResponse(const CreateRoomResponse& response);
	static std::vector<char> SerializeResponse(const getHighScoreResponse& response);
	static std::vector<char> SerializeResponse(const getPersonalStatsResponse& response);

private:

};




