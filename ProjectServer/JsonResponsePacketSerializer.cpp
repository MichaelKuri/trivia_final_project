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
    std::vector<char> buffer(1 + 4 + dataLength);

    // set the code (1 byte) - example
    buffer[0] = 0x01;

    // set the data length (4 bytes)
    // using memcpy to convert the length into a 4-byte sequence in little-endian format
    std::memcpy(buffer.data() + 1, &dataLength, 4);

    // copy the JSON data into the buffer
    std::memcpy(buffer.data() + 1 + 4, jsonString.data(), dataLength);

    return buffer;
}
