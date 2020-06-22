#include "Level.h"

Level::Level(uint entitiesInRow, uint startY, sf::Time enemyTimeMoving, uint levelNumber) : entitiesInRow(entitiesInRow), startY(startY), enemyTimeMoving(enemyTimeMoving), levelNumber(levelNumber), fillColor(sf::Color(240, 240, 240, 255)) { load(); }

Level::~Level() {}

void Level::draw(sf::RenderTarget& Target, sf::RenderStates States) const { Target.draw(levelText); }

void Level::load()
{
	if (!fontLoaded) { font.loadFromFile("assets/CubicCoreMono.ttf"); fontLoaded = true; }
	levelText.setString("level: " + std::to_string(levelNumber));
	levelText.setFont(font);
	levelText.setCharacterSize(36);
	levelText.setPosition(216, 16);
	levelText.setFillColor(fillColor);
}