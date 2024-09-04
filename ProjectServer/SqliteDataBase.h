#pragma once
#include <string>
#include "IDatabase.h"
class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase() { open(); };
	bool open();
	//bool close();
	//login operations
	int doesUserExist(std::string);
	int doesPasswordMatch(std::string, std::string);
	int addNewUser(std::string, std::string, std::string);
	//game information and statistic operations
	std::list<Question> getQuestions(int);
	float getPlayerAverageAnswerTime(std::string);
	int getNumOfCorrectAnswers(std::string);
	int getNumOfTotalAnswers(std::string);
	int getNumOfPlayerGames(std::string);
	int getPlayerScore(std::string);
	std::vector<std::string> getHighScores();

private:
	std::string dbName = "triviaDb";
};

