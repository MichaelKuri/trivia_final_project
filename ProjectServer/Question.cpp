#include "Question.h"




Question::Question(char* qu, char* ans1, char* ans2, char* ans3, char* ans4, int correctAns)
{
	m_question = qu;
	m_possibleAnswers.push_back(ans1);
	m_possibleAnswers.push_back(ans2);
	m_possibleAnswers.push_back(ans3);
	m_possibleAnswers.push_back(ans4);
	m_correct_answer = correctAns;
}

std::string Question::getQuestion()
{
	return m_question;
}


std::vector<std::string> Question::getPossibleAnswers()
{
	return m_possibleAnswers;
}


int Question::getCorrectAnswerId()
{
	return m_correct_answer;
}
