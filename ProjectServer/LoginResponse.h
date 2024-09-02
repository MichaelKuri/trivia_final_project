#pragma once

class LoginResponse
{
public:
	LoginResponse(unsigned int status);
	~LoginResponse();
	unsigned int _status;
private:

};

LoginResponse::LoginResponse(unsigned int status)
{
	this->_status = status;
}

LoginResponse::~LoginResponse()
{


}