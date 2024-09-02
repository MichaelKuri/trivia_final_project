#pragma once
#include <string>

class ErrorResponse
{
public:
	ErrorResponse();
	~ErrorResponse();
	std::string message;
private:

};

ErrorResponse::ErrorResponse()
{
}

ErrorResponse::~ErrorResponse()
{
}