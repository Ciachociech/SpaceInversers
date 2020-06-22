#include <random>

#include "EntityController.h"

std::default_random_engine gen1;
std::uniform_int_distribution<int> dist1(0, 99);

EntityController::EntityController() : entities(), gameArea(), bulletCounter(0), shieldCounter(0), enemyCounter(0), isRight(true), dir(right), isAllyBullet(false), dirCycles(0), distMax(99) {}

EntityController::~EntityController() {}

Entity& EntityController::getHero() const { return *hero; }

Entity& EntityController::getEntity(uint it) const { return *entities[it]; }

void EntityController::remove(int it) { entities.erase(entities.begin() + it); }

void EntityController::startGenerate(sf::IntRect& area) {
	gameArea = area;
	hero = std::make_unique<Hero>(628, 672, gameArea, true);
	entities.push_back(std::make_unique<Hero>(628, 80, gameArea, false));
	for (int i = 0; i < 4; i++)
	{
		entities.push_back(std::make_unique<Shield>(320 + 192 * i, 576, gameArea));
		entities.push_back(std::make_unique<Shield>(336 + 192 * i, 576, gameArea));
		entities.push_back(std::make_unique<Shield>(352 + 192 * i, 576, gameArea));
		entities.push_back(std::make_unique<Shield>(368 + 192 * i, 576, gameArea));
		entities.push_back(std::make_unique<Shield>(320 + 192 * i, 592, gameArea));
		entities.push_back(std::make_unique<Shield>(336 + 192 * i, 592, gameArea));
		entities.push_back(std::make_unique<Shield>(352 + 192 * i, 592, gameArea));
		entities.push_back(std::make_unique<Shield>(368 + 192 * i, 592, gameArea));
		entities.push_back(std::make_unique<Shield>(320 + 192 * i, 608, gameArea));
		entities.push_back(std::make_unique<Shield>(368 + 192 * i, 608, gameArea));
		shieldCounter += 10;
	}
}

void EntityController::generate(const Level& level) {
	for (uint i = 0; i < level.entitiesInRow; i++)
	{
		for (uint j = 0; j < 4; j++)
		{
			entities.push_back(std::make_unique<Enemy>(216 + 64 * i, level.startY + 48 * j, gameArea, i, j)); enemyCounter++;
		}
	}
	dirCycles = 0;
	distMax = 39 + 240 - level.startY;
	if (distMax < 19) { distMax = 19; }
	dist1 = std::uniform_int_distribution<int>(0, distMax);
}

void EntityController::createBullet(Entity& entity)
{
	if(entity.getIsFriendly()) 
	{ 
		if (!isAllyBullet) { entities.push_back(std::make_unique<Bullet>(entity, gameArea)); isAllyBullet = true; bulletCounter++; }
	}
	else { entities.push_back(std::make_unique<Bullet>(entity, gameArea)); bulletCounter++; }
}

void EntityController::exterminate() { entities.clear(); enemyCounter = 0; shieldCounter = 0; bulletCounter = 0; }

void EntityController::deleteAllBullets() 
{ 
	for (uint it = shieldCounter + 1; it < entities.size(); it++) { entities.pop_back(); } 
	bulletCounter = 0; 
	isAllyBullet = false; 
}

void EntityController::moveBullets() 
{
	for (uint it = static_cast<uint>(entities.size()) - 1; it > shieldCounter + enemyCounter; it--)
	{
		if (getEntity(it).getCoords().y > 736) 
		{ 
			if (getEntity(it).getIsFriendly() == true) { isAllyBullet = false; }
			remove(it); bulletCounter--;
		}
		else 
		{ 
			getEntity(it).refreshPosition({ 0,8 });
		}
	}
}

void EntityController::moveEntity(bool isPlayable, float moveX, float moveY) {
	if (isPlayable) 
	{ 
		getHero().refreshPosition({ moveX, moveY }); 
		getEntity(0).refreshPosition({ getHero().getCoords().x - getEntity(0).getCoords().x, moveY }); }
	if (!isPlayable) 
	{
		float borderX = checkBorders(true);
		if (borderX <= 216 || borderX >= 1016) 
		{ 
			dir = down; 
			isRight = !isRight; 
			dirCycles++;
			if (distMax > 19) { distMax -= 5; }
			else { distMax = 19; }
			dist1 = std::uniform_int_distribution<int>(0, distMax);
		}
		else if (isRight) { dir = right; }
		else if (!isRight) { dir = left; }
		for (uint it = shieldCounter + 1; it <= shieldCounter + enemyCounter; it++) 
		{
			switch (dir)
			{
			case right: { getEntity(it).refreshPosition({ 16, 0 }); break; }
			case left: { getEntity(it).refreshPosition({ -16, 0 }); break; }
			case down: { getEntity(it).refreshPosition({ 0, 8 }); break; }
			}
			if (dist1(gen1) == 1) { createBullet(getEntity(it)); }
		}
	}
}

uint EntityController::checkCollision(bool isEndurance) 
{
	int bonusPoints = 0;
	sf::FloatRect entityBounds1, entityBounds2;
	for (uint j = shieldCounter + enemyCounter + 1; j < entities.size(); j++)
	{
		if (getEntity(j).getHP() > 0)
		{
			entityBounds1 = getEntity(j).getGlobalBounds();
			entityBounds2 = getHero().getGlobalBounds();
			if ((getEntity(j).getIsFriendly()) && (entityBounds1.intersects(entityBounds2)))
			{
				if (isEndurance) { getHero().damage(); heroHit = true; }
				getEntity(j).damage(); isAllyBullet = false;
			}
			else if ((!getEntity(j).getIsFriendly()) && (entityBounds1.intersects(entityBounds2)))
			{
				getHero().damage(); getEntity(j).damage(); heroHit = true;
			}
			for (uint i = shieldCounter + 1; i <= shieldCounter + enemyCounter; i++)
			{
				if (getEntity(i).getHP() > 0)
				{
					entityBounds2 = getEntity(i).getGlobalBounds();
					if (getEntity(j).getIsFriendly() && (entityBounds1.intersects(entityBounds2)))
					{
						bonusPoints += getEntity(i).damage(); getEntity(j).damage(); isAllyBullet = false;
					}
				}
			}
			for (uint i = 1; i <= shieldCounter; i++)
			{
				entityBounds2 = getEntity(i).getGlobalBounds();
				if (entityBounds1.intersects(entityBounds2))
				{
					getEntity(i).damage();
					if (getEntity(j).getIsFriendly() == true) { isAllyBullet = false; }
					getEntity(j).damage();
				}
			}
		}
	}
	checkEntities();
	return bonusPoints;
}

uint EntityController::entityCount() const { return static_cast<uint>(entities.size()); }

void EntityController::checkEntities()
{
	if (heroHit == true) { if(getHero().prepareToDestroy(sf::milliseconds(1000))) { heroHit = false; } }
	for (uint it = static_cast<uint>(entities.size()) - 1; it > shieldCounter + enemyCounter; it--)
	{ 
		if (getEntity(it).getHP() <= 0) 
		{ 
			if (getEntity(it).prepareToDestroy(sf::milliseconds(1000))) { entities[it].reset(); remove(it); bulletCounter--; }
		}
	}
	for (uint it = shieldCounter + enemyCounter; it > shieldCounter; it--) 
	{ 
		if (getEntity(it).getHP() <= 0)
		{
			if (getEntity(it).prepareToDestroy(sf::milliseconds(1000))) { entities[it].reset(); remove(it); enemyCounter--; }
		}
	}
	for (uint it = shieldCounter; it > 0; it--) { if (getEntity(it).getHP() == 0) { entities[it].reset(); remove(it); shieldCounter--; } }
}

uint EntityController::getDirCycles() { return dirCycles; }

float EntityController::checkBorders(bool isX)
{
	float borderValue;
	if (isX) { borderValue = 640; }
	else { borderValue = 200; }
	for (uint it = shieldCounter + 1; it <= shieldCounter + enemyCounter; it++)
	{
		float coord;
		if (isX) 
		{ 
			coord = getEntity(it).getCoords().x; 
			switch (dir)
			{
			case right: { if (borderValue < coord) { borderValue = coord; } }
			case left: { if (borderValue > coord) { borderValue = coord; } }
			}
		}
		else 
		{ 
			coord = getEntity(it).getCoords().y;
			if (borderValue < coord) { borderValue = coord; }
		}
	}
	return borderValue;
}

uint EntityController::getEntityCount() { return enemyCounter; }
