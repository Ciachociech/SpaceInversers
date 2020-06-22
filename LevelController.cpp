#include "LevelController.h"

LevelController::LevelController() : actualLevel(0) { generate(); }

LevelController::~LevelController() {}

void LevelController::generate()
{
	uint it = 1, entitiesInRow = 7, startY = 240, enemyTimeMoving = 700;
	for (startY; startY < 500; startY += 2, it)
	{
		if (it < 4) { entitiesInRow++; }
		else { if (enemyTimeMoving > 250) { enemyTimeMoving = 700 - 25 * (it - 3); } }
		levels.push_back(std::make_unique<Level>(entitiesInRow, startY, sf::milliseconds(enemyTimeMoving), it));
		it++;
	}
}

Level& LevelController::getLevel(uint it) const { return *levels[it]; }

uint LevelController::getActualLevel() const { return actualLevel; }

void LevelController::levelUp() { actualLevel++; }
