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


	static std::vector<char> SerializeResponse(const ErrorResponse& response);
	static std::vector<char> SerializeResponse(const LoginResponse& response);
	static std::vector<char> SerializeResponse(const SignupResponse& response);
	static std::vector<char> ConvertJsonToBuffer(const json& j);

private:

};

JsonResponsePacketSerializer::JsonResponsePacketSerializer()
{

}

JsonResponsePacketSerializer::~JsonResponsePacketSerializer()
{
}




