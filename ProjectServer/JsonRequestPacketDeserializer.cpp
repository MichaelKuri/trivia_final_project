#include "JsonRequestPacketDeserializer.h"





LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::vector<char>& buffer)
{
    std::string jsonString(buffer.begin() , buffer.end()); 
    return parseLoginRequest(jsonString);
}


SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::vector<char>& buffer)
{
    std::string jsonString(buffer.begin(), buffer.end()); 
    return parseSignupRequest(jsonString);
}


LoginRequest JsonRequestPacketDeserializer::parseLoginRequest(const std::string& jsonString)
{
    json j = json::parse(jsonString);
    LoginRequest loginReq;
    loginReq.username = j["username"].get<std::string>();
    loginReq.password = j["password"].get<std::string>();
    return loginReq;
}


SignupRequest JsonRequestPacketDeserializer::parseSignupRequest(const std::string& jsonString)
{
    json j = json::parse(jsonString);
    SignupRequest signupReq;
    signupReq.username = j["username"].get<std::string>();
    signupReq.password = j["password"].get<std::string>();
    signupReq.email = j["email"].get<std::string>();
    return signupReq;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const std::vector<char>& buffer)
{


}


JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::vector<char>& buffer)
{


}


CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<char>& buffer)
{


}
