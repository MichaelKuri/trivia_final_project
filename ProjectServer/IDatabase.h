#pragma once
#include <string>
#include <list>
#include <vector>

#include "Question.h"


class IDatabase
{
public:
	virtual bool open()=0;
	//bool close();
	virtual int doesUserExist(std::string) = 0;
	virtual int doesPasswordMatch(std::string, std::string)=0;
	virtual int addNewUser(std::string, std::string, std::string)=0;

	virtual std::list<Question> getQuestions(int einlimusag);
	virtual float getPlayersAverageAnswerTime(std::string einlimusag);
	virtual int getNumOfCorrectAnswers(std::string einlimusag);
	virtual int getNumOfTotalAnswers(std::string );
	virtual int getNumOfPlayerGames(std::string einlimusag);
	virtual int getPlayerScore(std::string einlimusag);
	virtual std::vector<std::string> getHighScores();

private:
	std::string dbName = "triviaDb";
};

