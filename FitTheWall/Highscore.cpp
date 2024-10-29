#include "Highscore.h"

Highscore::Highscore()
{
	newName = "Name";
	newScore = 0;
}

Highscore::~Highscore()
{
}

void Highscore::compairHigScore()
{
	name[0] = ReadHigscore()[0];
	name[1] = ReadHigscore()[2];
	name[2] = ReadHigscore()[4];

	highscore[0] = stoi(ReadHigscore()[1]);
	highscore[1] = stoi(ReadHigscore()[3]);
	highscore[2] = stoi(ReadHigscore()[5]);

	// compare old and new score
	if (highscore[0] < newScore)
	{
		highscore[2] = highscore[1];
		highscore[1] = highscore[0];
		highscore[0] = newScore;
		name[2] = name[1];
		name[1] = name[0];
		name[0] = newName;
	}
	else if (highscore[1] < newScore)
	{
		highscore[2] = highscore[1];
		highscore[1] = newScore;
		name[2] = name[1];
		name[1] = newName;
	}
	else if (highscore[2] < newScore)
	{
		highscore[2] = newScore;
		name[2] = newName;
	}
	WriteHighscore();
}

void Highscore::setNewName(std::string name)
{
	newName = name;
}

void Highscore::SetNewScore(int score)
{
	newScore = score;
}

int Highscore::GetNewScore()
{
	return newScore;
}

std::vector <std::string> Highscore::ReadHigscore()
{
	std::ifstream readFile("highscore.txt");
	std::vector <std::string> allLines;
	std::string lines;

	if (readFile.is_open())
	{
		while (getline(readFile, lines))
		{
			allLines.push_back(lines);

		}
	}

	readFile.close();
	return allLines;
}

void Highscore::WriteHighscore()
{
	//write to file
	std::ofstream outfile("highscore.txt");
	outfile << name[0] << std::endl;
	outfile << highscore[0] << std::endl;
	outfile << name[1] << std::endl;
	outfile << highscore[1] << std::endl;
	outfile << name[2] << std::endl;
	outfile << highscore[2] << std::endl;
	outfile.close();
}

void Highscore::Reset()
{
	newName = "Name";
	newScore = 0;
}

std::string Highscore::GetNewName()
{
	return newName;
}
