#pragma once
#include <string>
class IDatabase
{
public:
	IDatabase() { open(); };
	bool open();
	bool close();
	int doesUserExist(std::string);
	int doesPasswordMatch(std::string, std::string);
	int addNewUser(std::string, std::string, std::string);
private:
	std::string dbName = "triviaDb";
};

