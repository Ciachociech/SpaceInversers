#pragma once

#include <vector>
#include "Level.h"

typedef std::vector<Level_uptr> VecLevel;

class LevelController
{
private:
	VecLevel levels;
	uint actualLevel;

	void generate();
public:
	LevelController();
	~LevelController();

	Level& getLevel(uint it) const;
	void levelUp();

	uint getActualLevel() const;
};

