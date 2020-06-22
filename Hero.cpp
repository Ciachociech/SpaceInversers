#include "Hero.h"

Hero::Hero(float coordX, float coordY, sf::IntRect& gameArea, bool playable) : Entity(coordX, coordY, 48, 24, 3, gameArea, 1, 4, true, playable), shotCooldown(1000)
{
	if (playable) { loadImage("assets/vehicle3.png"); loadDestruct("assets/vehicleDest.png"); }
	else { loadImage("assets/satelite.png"); }
	create(); load();
}

Hero::~Hero() {}

void Hero::refreshPosition(sf::Vector2f translate) 
{ 
	translate.y = 0; 
	if ((getCoords().x == 216) && (translate.x < 0)) { translate.x = 0; }
	if ( (getCoords().x == 1016) && (translate.x > 0) ) { translate.x = 0; }
	Entity::refreshPosition(translate);
}

int Hero::damage(int value) { Entity::damage(value); load(); return 0; }

float Hero::getShotCooldown() { return shotCooldown; }