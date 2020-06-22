#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Menu.h"
#include "Game.h"
#include "ScoreController.h"

enum InstanceState { splashscreen, mainmenu, difficult, highscores, about, gameLaunched, gamePaused, gameOver };
enum KeyboardState { pausemenu = -1, none = 0 };

class Instance
{
private:
	sf::RenderWindow window;
	sf::Color backgroundColor, fillColor;
	sf::Time shotCooldown = sf::Time::Zero, enemyCooldown = sf::Time::Zero, countTime = sf::Time::Zero;
	sf::IntRect instanceArea;
	sf::String nicknameInput = "";
	sf::Text nicknameText;
	sf::Font font;

	bool isEntered = false, isEntering = false, startCounting = false;
	uint lastScore, bestScore;

	InstanceState instanceState;
	KeyboardState keyboardState;
	Menu mainMenu, difficultMenu, scoresMenu, aboutMenu, pauseMenu, gameOverMenu;
	ScoreController scoreControl;
	Game_uptr actualGame;

	void splashScreen();
	void eventPoll();
	void keyboardInput();
	void refresh();
	void render();
	void wait(unsigned int mseconds);
	bool count(unsigned int mseconds);
	void prepareText();
	void additions();
public:
	Instance();
	virtual ~Instance();
	void launch();
};

