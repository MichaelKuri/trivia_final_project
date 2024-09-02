#include "JsonRequestPacketDeserializer.h"



JsonRequestPacketDeserializer::JsonRequestPacketDeserializer()
{

}


JsonRequestPacketDeserializer::~JsonRequestPacketDeserializer()
{

}


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<char>& buffer)
{
    std::string jsonString(buffer.begin() + 5, buffer.end()); 
    return parseLoginRequest(jsonString);
}


SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<char>& buffer)
{
    std::string jsonString(buffer.begin() + 5, buffer.end()); 
    return parseSignupRequest(jsonString);
}


LoginRequest JsonRequestPacketDeserializer::parseLoginRequest(const std::string& jsonString)
{
    json j = json::parse(jsonString);
    LoginRequest loginReq;
    loginReq.username = j["username"].get<std::string>();
    loginReq.username = j["password"].get<std::string>();
    return loginReq;
}


SignupRequest JsonRequestPacketDeserializer::parseSignupRequest(const std::string& jsonString)
{
    json j = json::parse(jsonString);
    SignupRequest signupReq;
    signupReq.username = j["username"].get<std::string>();
    signupReq.username = j["password"].get<std::string>();
    signupReq.username = j["email"].get<std::string>();
    return signupReq;
}
