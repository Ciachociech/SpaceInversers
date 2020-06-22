#include "Enemy.h"

std::vector<std::string> enemyPathes({ "assets/invaderANorm.png", "assets/invaderBNorm.png", "assets/invaderCNorm.png"});
std::vector<std::string> destructPathes({ "assets/invaderADest.png", "assets/invaderBDest.png", "assets/invaderCDest.png" });

Enemy::Enemy(float coordX, float coordY, sf::IntRect& gameArea, uint column, uint row) : Entity(coordX, coordY, 48, 32, 1, gameArea, 2, 4, false, false), row(row), column(column), points((row==2?40:10*(row+1))) 
{ 
	imageSelector(); create();
}

Enemy::~Enemy() {}

void Enemy::imageSelector()
{
	switch (row)
	{
	case 0: { loadImage(enemyPathes[0]); loadDestruct(destructPathes[0]);  break; }
	case 1: { loadImage(enemyPathes[1]); loadDestruct(destructPathes[1]); break; }
	case 2: { loadImage(enemyPathes[2]); loadDestruct(destructPathes[2]); break; }
	case 3: { loadImage(enemyPathes[2]); loadDestruct(destructPathes[2]); break; }
	}
}

void Enemy::refreshPosition(sf::Vector2f translate) { Entity::refreshPosition(translate); }

int Enemy::damage(int value) { Entity::damage(); return points; }

uint Enemy::getPoints() { return points; }

int Enemy::entityID() { return row; }
