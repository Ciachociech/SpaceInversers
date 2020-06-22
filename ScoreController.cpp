#include <fstream>

#include "ScoreController.h"

ScoreController::ScoreController() : scores(), isRead(false), oldRecord(0) { }

ScoreController::~ScoreController() {}

void ScoreController::loadFromFile(bool isEndurance)
{
	scores.clear();
	std::ifstream file;
	if (!isEndurance) { filepath = "highscores_class.dat"; }
	else { filepath = "highscores_endur.dat"; }
	file.open(filepath);
	std::string nickname = "";
	int points = 0, it = 1;
	scores.push_back(std::make_unique<Score>(nickname, points, true));
	while (file.good())
	{
		file >> nickname;
		file >> points;
		scores.push_back(std::make_unique<Score>(nickname, points, false));
		getScore(it).refreshPosition(it);
		it++;
	}
	file.close();
	oldRecord = getScore(1).getPoints();
}

void ScoreController::update(uint pts)
{ 
	scores[0]->addPoints(pts);
	if (isBestBeaten()) { scores[1]->showPoints(scores[0]->getPoints()); }
}

bool ScoreController::isBestBeaten()
{
	if (scores[0]->getPoints() >= scores[1]->getPoints()) { return true; }
	return false;
}

bool ScoreController::checkSaving()
{
	if (scores[0]->getPoints() > scores[5]->getPoints()) { return true; }
	return false;
}

void ScoreController::changeOrder(sf::String enteredNickname) {
	if (enteredNickname == "") { enteredNickname = "(nameless)"; }
	uint it = 6;
	bool isChanged;
	do
	{
		isChanged = false;
		if (scores[0]->getPoints() > scores[it - 1]->getPoints()) { --it; isChanged = true; }
	} while ((it != 0) && isChanged);
	if (it < 6)
	{
		scores.pop_back(); 
		scores.insert(scores.begin() + it, std::make_unique<Score>(enteredNickname, scores[0]->getPoints(), false));
		getScore(0).reset();
	}
	saveToFile();
}

void ScoreController::saveToFile() {
	std::ofstream file(filepath, std::ios::out);
	for (int it = 1; it < 6; it++)
	{
		file << scores[it]->getNickname() << " " << scores[it]->getPoints() << std::endl;
	}
	file.close();
}

Score& ScoreController::getScore(uint it) const { return *scores[it]; }

void ScoreController::changeScoreMode() 
{
	getScore(0).changeScoreMode(); getScore(0).refreshPosition(0);
	getScore(1).changeScoreMode(); getScore(1).refreshPosition(1);
}