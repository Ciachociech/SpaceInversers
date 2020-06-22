#pragma once

#include <vector>
#include "Score.h"

typedef std::vector<std::unique_ptr<sf::Text>> VecText;
typedef std::vector<Score_uptr> VecScore;

class ScoreController
{
private:
	VecScore scores;

	bool isRead;
	uint oldRecord;
	std::string filepath;

	void saveToFile();
public:
	ScoreController();
	~ScoreController();

	void update(uint pts);
	bool isBestBeaten();
	void changeOrder(sf::String enteredNickname="");
	void changeScoreMode();
	void loadFromFile(bool isEndurance);
	bool checkSaving();

	Score& getScore(uint it) const;
};

