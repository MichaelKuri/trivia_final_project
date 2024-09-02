#pragma once


class SignupResponse
{
public:
	SignupResponse(unsigned int status);
	~SignupResponse();
	unsigned int _status;

private:

};

SignupResponse::SignupResponse(unsigned int status)
{
	this->_status = status;
}

SignupResponse::~SignupResponse()
{

}