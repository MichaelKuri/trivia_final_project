#pragma once
#include <string>
#include "IDatabase.h"
#include<list>
#include "Question.h"
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
	float getPlayerAverageAnswerTime(std::string userName);
	int getNumOfCorrectAnswers(std::string userName);
	int getNumOfTotalAnswers(std::string userName);
	int getNumOfPlayerGames(std::string userName);
	int getPlayerScore(std::string userName);
	std::vector<std::string> getHighScores();

private:
	std::string dbName = "triviaDb";
};

