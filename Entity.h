#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

typedef unsigned int uint;

class Entity : public sf::Drawable 
{
private:
	uint imageStages, destructStages, animationStage = 0; int hp;
	bool drawSprite, isExploding;

	bool isFriendly, fontLoaded = false, hpShown;

	sf::Vector2f coords;

	sf::Image entityImage, entityDestruct;
	sf::Texture entityTexture;
	const sf::Vector2i spriteSize;
	sf::Sprite entitySprite;
	sf::IntRect gameArea;
	sf::Text hpText;
	sf::Font font;
	sf::Color fillColor;
	sf::Time damageTime, animateTime;
	sf::Clock clock;
public:
	Entity(float coordX, float coordY, int sizeX, int sizeY, int hp, sf::IntRect& gameArea, uint imageStages, uint destructStages, bool isFriendly, bool hpShown);
	virtual ~Entity() = 0;

	virtual void create();
	virtual void loadImage(std::string path);
	virtual void loadDestruct(std::string path);
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	virtual void refreshPosition(sf::Vector2f position);
	virtual int damage(int value=1);
	sf::FloatRect getGlobalBounds();
	virtual void load();
	virtual int entityID();
	virtual void animate(sf::Time tileTime);
	virtual bool prepareToDestroy(sf::Time deathTime);

	sf::Vector2f getCoords();
	const sf::Vector2i getSpriteSize();
	bool getIsFriendly();
	sf::IntRect getGameArea();
	int getHP();
	bool getDrawSprite();
};

typedef std::unique_ptr<Entity> Entity_uptr;