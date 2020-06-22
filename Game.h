#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "EntityController.h"
#include "LevelController.h"
#include "ScoreController.h"

class Game : public sf::Drawable
{
private:
	sf::IntRect gameArea;

	EntityController entityControl;
	LevelController levelControl;
	ScoreController scoreControl;

	bool isEndurance, stopShooting;
public:
	Game(sf::IntRect gameArea, bool isEndurance);
	virtual ~Game();
	
	void start();
	void doLoop(sf::Time& enemyCooldown);
	void notInGame();
	bool checkConditions();
	void levelUp();
	virtual void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	int keyboardInput();
	bool checkHiScores(uint mode, sf::String enteredNickname="");
	uint getActualScore();
	uint getBestScore();
};

typedef std::unique_ptr<Game> Game_uptr;