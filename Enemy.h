#pragma once

#include <random>
#include <memory>

#include "Entity.h"

class Enemy : public Entity
{
private:
	uint row, column, points;

	void imageSelector();
public:
	Enemy(float coordX, float coordY, sf::IntRect& gameArea, uint column, uint row);
	virtual ~Enemy();

	void refreshPosition(sf::Vector2f translate) override;
	int damage(int value=1) override;
	int entityID() override;

	uint getPoints();
};

typedef std::unique_ptr<Enemy> Enemy_uptr;