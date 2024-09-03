#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>
class LoginManager
{
public:
	LoginManager(IDatabase* database) : _m_database(database) {};
	bool signup(std::string, std::string, std::string);
	bool login(std::string, std::string);
	bool logout(std::string);

private:
	IDatabase* _m_database;
	std::vector<LoggedUser>	_m_loggedUsers;
};
