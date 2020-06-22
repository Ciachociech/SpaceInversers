#pragma once

#include <vector>

#include "Bullet.h"
#include "Enemy.h"
#include "Hero.h"
#include "Shield.h"
#include "Level.h"

typedef std::vector<Entity_uptr> VecEntity;

enum Direction { left, down, right };

class EntityController
{
private:
	VecEntity entities;
	Entity_uptr hero;

	uint shieldCounter, enemyCounter, bulletCounter, dirCycles;
	int distMax;
	sf::IntRect gameArea;
	Direction dir;
	bool isRight, isAllyBullet, heroHit = false;

	void remove(int it);
	void checkEntities();
public:
	EntityController();
	~EntityController();

	Entity& getHero() const;
	Entity& getEntity(uint it) const;
	void startGenerate(sf::IntRect& area);
	void generate(const Level& level);
	void createBullet(Entity& entity);
	void exterminate();
	void deleteAllBullets();
	void moveBullets();
	void moveEntity(bool isPlayable, float moveX = 0, float moveY = 0);
	uint checkCollision(bool isEndurance);
	uint entityCount() const;
	float checkBorders(bool isX);

	uint getDirCycles();
	uint getEntityCount();
};

