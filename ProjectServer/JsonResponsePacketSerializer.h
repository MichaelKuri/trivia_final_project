#pragma once
#include <vector>
#include "ErrorResponse.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include <vector>
#include <cstring>
#include "json.hpp"

using json = nlohmann::json;


class JsonResponsePacketSerializer
{
public:
	JsonResponsePacketSerializer();
	~JsonResponsePacketSerializer();


	std::vector<char> SerializeResponse(const ErrorResponse& response);
	std::vector<char> SerializeResponse(const LoginResponse& response);
	std::vector<char> SerializeResponse(const SignupResponse& response);
	std::vector<char> ConvertJsonToBuffer(const json& j);

private:

};

JsonResponsePacketSerializer::JsonResponsePacketSerializer()
{

}

JsonResponsePacketSerializer::~JsonResponsePacketSerializer()
{
}




