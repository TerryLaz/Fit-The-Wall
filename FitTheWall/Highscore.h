#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Highscore
{
private:
	int newScore;
	std::string newName;
	std::string name[3];
	int highscore[3];
	void WriteHighscore();
public:
	Highscore();
	~Highscore();
	void compairHigScore();
	void SetNewScore(int score);
	int GetNewScore();
	void Reset();
	void setNewName(std::string name);
	std::string GetNewName();
	std::vector <std::string> ReadHigscore();
};

