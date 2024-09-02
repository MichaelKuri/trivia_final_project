#pragma once
#include <vector>
#include "LoginRequest.h"
#include "SignupRequest.h"
#include <cstring>
#include <string>

#include "json.hpp"

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
    JsonRequestPacketDeserializer();
    ~JsonRequestPacketDeserializer();

    LoginRequest deserializeLoginRequest(const std::vector<char>& buffer);
    SignupRequest deserializeSignupRequest(const std::vector<char>& buffer);

private:

    // i add helping func to help me with the buffer
    LoginRequest parseLoginRequest(const std::string& jsonString);
    SignupRequest parseSignupRequest(const std::string& jsonString);
};
