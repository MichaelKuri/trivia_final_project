#pragma once
#include <string>
class  LoginRequest
{
public:
	 LoginRequest();
	~ LoginRequest();

	std::string username;
	std::string password;

private:

};

 LoginRequest:: LoginRequest()
{
}

 LoginRequest::~ LoginRequest()
{
}