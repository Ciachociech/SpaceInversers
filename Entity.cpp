#include "Entity.h"

Entity::Entity(float coordX, float coordY, int sizeX, int sizeY, int hp, sf::IntRect& gameArea, uint imageStages, uint destructStages, bool isFriendly, bool hpShown) : coords(coordX, coordY), spriteSize(sizeX, sizeY), hp(hp), gameArea(gameArea), animationStage(0), imageStages(imageStages), destructStages(destructStages), drawSprite(false), isExploding(false), isFriendly(isFriendly), hpShown(hpShown), fillColor(sf::Color(240, 240, 240, 255)) { }

Entity::~Entity() {}

void Entity::create()
{
	entityTexture.loadFromImage(entityImage, sf::IntRect(0, 0, static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)));
	entitySprite.setTexture(entityTexture);
	entitySprite.setPosition({ static_cast<float>(coords.x), static_cast<float>(coords.y) });
	drawSprite = true;
}

void Entity::loadImage(std::string path) { entityImage.loadFromFile(path); }

void Entity::loadDestruct(std::string path) { entityDestruct.loadFromFile(path); }

void Entity::draw(sf::RenderTarget& Target, sf::RenderStates States) const 
{ 
	if (drawSprite) { Target.draw(entitySprite); } 
	if (hpShown) { Target.draw(hpText); }
}

void Entity::refreshPosition(sf::Vector2f translate) 
{ 
	if ((getHP() > 0) && (!isExploding)) { coords += translate; entitySprite.setPosition(coords); } }

int Entity::damage(int value) 
{ 
	damageTime = sf::Time::Zero;
	hp -= value;
	if (value > 0) { isExploding = true; animationStage = 0; }
	return 0;
}

bool Entity::getIsFriendly() { return isFriendly; }

sf::Vector2f Entity::getCoords() { return this->coords; }

const sf::Vector2i Entity::getSpriteSize() { return spriteSize; }

sf::FloatRect Entity::getGlobalBounds() { return entitySprite.getGlobalBounds(); }

sf::IntRect Entity::getGameArea() { return gameArea; }

int Entity::getHP() { return hp; }

bool Entity::getDrawSprite() { return drawSprite; }

void Entity::load()
{
	if (!fontLoaded) { font.loadFromFile("assets/CubicCoreMono.ttf"); fontLoaded = true; }
	std::string hpNumber = (getHP() < 10 ? "0" + std::to_string(getHP()) : (getHP() > 99 ? "99+" : std::to_string(getHP())));
	hpText.setString("lifes: x" + hpNumber);
	hpText.setFont(font);
	hpText.setCharacterSize(36);
	sf::FloatRect hpRect = hpText.getLocalBounds();
	hpText.setOrigin(hpRect.left + hpRect.width, 0);
	hpText.setPosition(1064, 16);
	hpText.setFillColor(fillColor);
}

int Entity::entityID() { return -1; }

void Entity::animate(sf::Time tileTime)
{
	if (animateTime > tileTime)
	{
		animateTime = sf::Time::Zero;
		if (!isExploding)
		{
			if (animationStage < imageStages) { animationStage++; }
			else { animationStage = 0; }
			entityTexture.loadFromImage(entityImage, sf::IntRect(static_cast<int>(spriteSize.x) * animationStage, 0, static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)));
		}
		else
		{
			if (animationStage < destructStages) { animationStage++; }
			else { animationStage = 0; }
			entityTexture.loadFromImage(entityDestruct, sf::IntRect(static_cast<int>(spriteSize.x) * animationStage, 0, static_cast<int>(spriteSize.x), static_cast<int>(spriteSize.y)));
		}
	}
	animateTime += clock.getElapsedTime();
	clock.restart();
}

bool Entity::prepareToDestroy(sf::Time deathTime)
{
	if (damageTime < deathTime) { damageTime += clock.getElapsedTime(); return false; }
	else { isExploding = false; return true; }
}