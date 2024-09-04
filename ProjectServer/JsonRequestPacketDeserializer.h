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
   

    static LoginRequest deserializeLoginRequest(const std::vector<char>& buffer);
    static SignupRequest deserializeSignupRequest(const std::vector<char>& buffer);

private:

    // i add helping func to help me with the buffer
    static LoginRequest parseLoginRequest(const std::string& jsonString);
    static SignupRequest parseSignupRequest(const std::string& jsonString);
};
