#pragma once
#include <string>
class IDatabase
{
public:
	bool open();
	//bool close();
	virtual int doesUserExist(std::string) = 0;
	virtual int doesPasswordMatch(std::string, std::string)=0;
	virtual int addNewUser(std::string, std::string, std::string)=0;
private:
	std::string dbName = "triviaDb";
};

