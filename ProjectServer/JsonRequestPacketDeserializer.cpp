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
    std::string buffer(buffer.begin(), buffer.end());
    json j = json::parse(buffer);
    GetPlayersInRoomRequest request;
    request.roomId = j["roomId"];
    return request;
}


JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::vector<char>& buffer)
{
    std::string jsonString(buffer.begin(), buffer.end());
    json j = json::parse(jsonString);
    JoinRoomRequest request;
    request.roomId = j["roomId"];  
    return request;
}


CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::vector<char>& buffer)
{
    std::string jsonString(buffer.begin(), buffer.end());
    json j = json::parse(jsonString);
    CreateRoomRequest request;
    request.roomName = j["roomName"].get<std::string>(); 
    request.maxUsers = j["maxUsers"].get<int>();
    request.questionCount = j["questionCount"].get<int>();
    request.answerTimeout = j["answerTimeout"].get<int>();
    return request;
}

