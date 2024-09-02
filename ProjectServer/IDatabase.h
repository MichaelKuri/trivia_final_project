#pragma once
#include <string>
class IDatabase
{
public:
	virtual bool open()=0;
	//bool close();
	virtual int doesUserExist(std::string) = 0;
	virtual int doesPasswordMatch(std::string, std::string)=0;
	virtual int addNewUser(std::string, std::string, std::string)=0;
private:
	std::string dbName = "triviaDb";
};

