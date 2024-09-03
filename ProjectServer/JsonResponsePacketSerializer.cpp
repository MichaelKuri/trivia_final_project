#include "JsonResponsePacketSerializer.h"




std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const ErrorResponse& response)
{
    json j;
    j["message"] = response.message;
    return ConvertJsonToBuffer(j);
}

std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const LoginResponse& response)
{
    json j;
    j["status"] = response._status;
    return ConvertJsonToBuffer(j);
}

std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const SignupResponse& response)
{
    json j;
    j["status"] = response._status;
    return ConvertJsonToBuffer(j);
}

std::vector<char> JsonResponsePacketSerializer::ConvertJsonToBuffer(const json& j)
{
    std::string jsonString = j.dump();

    // check the size of the JSON data
    std::size_t dataLength = jsonString.size();

    // create a buffer with size 1 (code) + 4 (length) + data length
    //std::vector<char> buffer(1 + 4 + dataLength);
    std::vector<char> buffer;
    char i = (char)1;
    buffer.push_back(i);
    // set the code (1 byte) - example
    //buffer[0] = 0x01;
    std::vector<char> sizeL;
    sizeL.push_back(dataLength>>24);
    sizeL.push_back(dataLength>>16);
    sizeL.push_back(dataLength>>8);
    sizeL.push_back(dataLength);
    
    // set the data length (4 bytes)
    // using memcpy to convert the length into a 4-byte sequence in little-endian format
    //std::memcpy(buffer.data() + 1, &dataLength, 4);
    for (size_t i = 0; i < 4; i++)
    {
        buffer.push_back(sizeL[i]);
    }
    // copy the JSON data into the buffer
    //std::memcpy(buffer.data() + 1 + 4, jsonString.data(), dataLength);
    for (size_t i = 0; i < dataLength; i++)
    {
        buffer.push_back(jsonString[i]);
    }
    return buffer;
}


std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const LogoutResponse& response)
{


}


std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const GetRoomsResponse& response)
{


}


std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const GetPlayersInRoomResponse& response)
{


}


std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const JoinRoomResponse& response)
{


}


std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const CreateRoomResponse& response)
{


}


std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const getHighScoreResponse& response)
{


}


std::vector<char> JsonResponsePacketSerializer::SerializeResponse(const getPersonalStatsResponse& response)
{



}
