#include "Bullet.h"

std::vector<std::string> bulletPathes({ "assets/bulletA.png", "assets/bulletB.png", "assets/bulletC.png", "assets/bulletH.png" });

Bullet::Bullet(Entity& entity, sf::IntRect& gameArea) : Entity(entity.getCoords().x + 24, entity.getCoords().y + entity.getSpriteSize().y - 1, 3, 16, 1, gameArea, 2, 4, entity.getIsFriendly(), false)
{
	imageSelector(entity.entityID()); loadDestruct("assets/bulletDest.png");
	create();
}

Bullet::~Bullet() {}

void Bullet::refreshPosition(sf::Vector2f translate) { translate.x = 0; Entity::refreshPosition(translate); }

bool Bullet::isDestroyable()
{
	if ((getCoords().y <= getGameArea().top + getGameArea().height) && (getCoords().y >= getGameArea().top)) { return false; }
	return true;
}

void Bullet::imageSelector(uint type)
{
	if(getIsFriendly()) { loadImage(bulletPathes[3]); }
	else
	{
		switch (type)
		{
		case 0: { loadImage(bulletPathes[0]); break; }
		case 1: { loadImage(bulletPathes[1]); break; }
		case 2: { loadImage(bulletPathes[2]); break; }
		case 3: { loadImage(bulletPathes[2]); break; }
		}
	}
}