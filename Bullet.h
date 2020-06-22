#pragma once
#include <memory>

#include "Entity.h"

class Bullet : public Entity
{
private:
	void imageSelector(uint type);
public:
	Bullet(Entity& entity, sf::IntRect& gameArea);
	virtual ~Bullet();

	void refreshPosition(sf::Vector2f translate) override;
	bool isDestroyable();
};

typedef std::unique_ptr<Bullet> Bullet_uptr;