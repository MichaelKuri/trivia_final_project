#pragma once
#include <string>


class SignupRequest
{
public:
	SignupRequest();
	~SignupRequest();

	std::string username;
	std::string password;
	std::string email;

private:

};

SignupRequest::SignupRequest()
{
}

SignupRequest::~SignupRequest()
{
}