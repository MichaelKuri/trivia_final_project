#pragma once
#include <string>

class LoggedUser
{
public:
	LoggedUser(std::string username) { _m_username = username; };
	inline std::string getUsername() { return _m_username; };



private:
	std::string _m_username;
};
