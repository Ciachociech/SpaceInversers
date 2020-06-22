#include "Game.h"

Game::Game(sf::IntRect gameArea, bool isEndurance) : gameArea(gameArea), isEndurance(isEndurance), entityControl(), scoreControl() { start(); }

Game::~Game() {}

void Game::start() 
{ 
	scoreControl.loadFromFile(isEndurance);
	entityControl.startGenerate(gameArea); 
	entityControl.generate(levelControl.getLevel(levelControl.getActualLevel()));
	scoreControl.changeScoreMode();
	scoreControl.getScore(0).reset();
}

void Game::doLoop(sf::Time& enemyCooldown) 
{ 
	uint points;
	if(enemyCooldown > levelControl.getLevel(levelControl.getActualLevel()).enemyTimeMoving - sf::milliseconds(5 * entityControl.getDirCycles()) - sf::milliseconds(5 * (40 - entityControl.getEntityCount())))
	{ 
		entityControl.moveEntity(false); 
		enemyCooldown = sf::Time::Zero;
	}
	points = entityControl.checkCollision(isEndurance);
	entityControl.moveBullets();
	scoreControl.update(points);
	checkConditions();
}

void Game::notInGame() {}

bool Game::checkConditions() 
{
	float borderY = entityControl.checkBorders(false);
	if (borderY > 520) { return true; }
	if (entityControl.getHero().getHP() == 0) { return true; }
	if (entityControl.getEntityCount() == 0) { levelUp(); }
	return false;
}

void Game::levelUp() 
{ 
	levelControl.levelUp();
	scoreControl.update(100 + 10 * levelControl.getActualLevel());
	entityControl.deleteAllBullets();  
	entityControl.generate(levelControl.getLevel(levelControl.getActualLevel())); 
	entityControl.getHero().damage(-1);
}

void Game::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	entityControl.getHero().animate(sf::milliseconds(240)); 
	Target.draw(entityControl.getHero());
	for (uint it = 0; it < entityControl.entityCount(); it++)
	{
		entityControl.getEntity(it).animate(sf::milliseconds(240));
		Target.draw(entityControl.getEntity(it));
	}
	Target.draw(levelControl.getLevel(levelControl.getActualLevel()));
	Target.draw(scoreControl.getScore(0));
	Target.draw(scoreControl.getScore(1));
}

int Game::keyboardInput()
{
	if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)))
	{
		if (!stopShooting) { entityControl.createBullet(entityControl.getEntity(0)); stopShooting = true; }
	}
	else { stopShooting = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { entityControl.moveEntity(true, -8, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { entityControl.moveEntity(true, 8, 0); }
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))) { return -1; }
	return 0;
}

bool Game::checkHiScores(uint mode, sf::String enteredNickname)
{
	switch (mode)
	{
	case 0: { return scoreControl.checkSaving(); break; }
	case 1: { scoreControl.changeOrder(enteredNickname); return true; break; }
	default: { return false; break; }
	}
}

uint Game::getActualScore() { return scoreControl.getScore(0).getPoints(); }

uint Game::getBestScore() { return scoreControl.getScore(1).getPoints(); }