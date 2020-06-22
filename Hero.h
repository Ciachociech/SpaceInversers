#pragma once
#include <memory>

#include "Entity.h"

class Hero : public Entity
{
private:
	float shotCooldown;
public:
	Hero(float coordX, float coordY, sf::IntRect& gameArea, bool playable);
	~Hero();

	void refreshPosition(sf::Vector2f translate) override;
	int damage(int value=1) override;
	
	float getShotCooldown();
};

typedef std::unique_ptr<Hero> Hero_uptr;