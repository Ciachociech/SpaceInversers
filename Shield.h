#pragma once

#include <memory>
#include "Entity.h"

class Shield : public Entity
{
private:
public:
	Shield(float coordX, float coordY, sf::IntRect& gameArea);
	virtual ~Shield();

	int damage(int value=1) override;
};

typedef std::unique_ptr<Shield> Shield_uptr;