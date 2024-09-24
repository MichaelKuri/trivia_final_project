#include "statisticsManager.h"
#include "IDatabase.h"

std::vector<std::string> StatisticsManager::getHighScore()
{
	return m_database->getHighScores();
}


std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::vector<std::string> stats;
	stats.push_back("total ans" + std::to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back("avg ans" + std::to_string(m_database->getPlayerAverageAnswerTime(username)));
	stats.push_back("player score" + std::to_string(m_database->getPlayerScore(username)));
	stats.push_back("correct ans" + std::to_string(m_database->getNumOfCorrectAnswers(username)));

	return stats;
}