#pragma once
#include <vector>
#include <string>

class Question
{
public:
	Question(char*, char*, char*, char*, char*, int);

	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	int getCorrectAnswerId();

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int m_correct_answer;

};

