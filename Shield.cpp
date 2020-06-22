#include "Shield.h"

std::vector<std::string> shieldPathes({"assets/shield0.png", "assets/shieldA.png", "assets/shieldB.png", "assets/shieldC.png", "assets/shieldD.png"});

Shield::Shield(float coordX, float coordY, sf::IntRect& gameArea) : Entity(coordX, coordY, 16, 16, 4, gameArea, 1, 0, true, false)
{
	loadImage(shieldPathes[4]);
	create();
}

Shield::~Shield() {}

int Shield::damage(int value)
{
	switch (getHP())
	{
	case 4: { loadImage(shieldPathes[3]); Entity::damage(); break; }
	case 3: { loadImage(shieldPathes[2]); Entity::damage(); break; }
	case 2: { loadImage(shieldPathes[1]); Entity::damage(); break; }
	case 1: { loadImage(shieldPathes[0]); Entity::damage(); break; }
	}
	create();
	return 0;
}
