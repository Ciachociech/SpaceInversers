#pragma once

#include <vector>

#include "Level.h"

typedef std::vector<Level_uptr> VecLevel;

class LevelCollection
{
private:
	VecLevel levels;
public:
	LevelCollection();
	~LevelCollection();

	VecLevel getLevel(uint it);
};

