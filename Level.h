#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

typedef unsigned int uint;

class Level : public sf::Drawable
{
private:
	uint levelNumber;
	bool fontLoaded = false;

	sf::Text levelText;
	sf::Font font;
	sf::Color fillColor;
public:
	const uint entitiesInRow;
	const uint startY;
	const sf::Time enemyTimeMoving;

	Level(uint entitiesInRow, uint startY, sf::Time enemyTimeMoving, uint levelNumber);
	~Level();

	void load();
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
};

typedef std::unique_ptr<Level> Level_uptr;