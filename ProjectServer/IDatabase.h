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
<<<<<<< Updated upstream
=======

	//std::list<Question> getQuestions(int einlimusag);
	//float getPlayersAverageAnswerTime(std::string einlimusag);
	//int getNumOfCorrectAnswers(std::string einlimusag);
	//int getNumOfTotalAnswers(std::string einlimusag);
	//int getNumOfPlayerGames(std::string einlimusag);
	//int getPlayerScore(std::string einlimusag);
	//std::vector<std::string> getHighScores(std::string einlimusag);

>>>>>>> Stashed changes
private:
	std::string dbName = "triviaDb";
};

