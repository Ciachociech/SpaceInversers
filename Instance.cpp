#include "Instance.h"

const sf::String windowTitle = "Space Inversers";

Instance::Instance() : window(sf::VideoMode(1280, 720), windowTitle), backgroundColor(31, 31, 31, 255), instanceArea(0,0,window.getSize().x,window.getSize().y), instanceState(splashscreen), keyboardState(none), mainMenu({ "PLAY", "HI-SCORES", "ABOUT", "EXIT" }, instanceArea, true, "assets/logo.png", 450), difficultMenu({ "", "CLASSIC", "ENDURANCE", "BACK TO MENU" }, instanceArea, true, "assets/logo.png", 450), scoresMenu({ "", "BACK TO MENU" }, instanceArea, false, "highscores"), aboutMenu({ "", "BACK TO MENU" }, instanceArea, false, "about"), pauseMenu({ "", "RESUME", "BACK TO MENU" }, instanceArea, false, "pause"), gameOverMenu({ "", "PLAY AGAIN", "BACK TO MENU" }, instanceArea, false, "game over"), scoreControl(), fillColor(sf::Color(240, 240, 240, 255)), lastScore(0), bestScore(0) {}

Instance::~Instance() {}

void Instance::launch()
{
	const int FPS = 60;
	const double frameDuration = 1000 / FPS;
	sf::Time frameTime = sf::Time::Zero;
	sf::Clock frameClock;
	additions();
	while (window.isOpen())
	{
		frameTime += frameClock.getElapsedTime();
		shotCooldown += frameClock.getElapsedTime();
		enemyCooldown += frameClock.getElapsedTime();
		frameClock.restart();
		if (frameTime.asMilliseconds() >= frameDuration)
		{
			eventPoll();
			keyboardInput();
			refresh();
			render();
			frameTime = sf::Time::Zero;
		}
	}
}


void Instance::splashScreen()
{
	// TODO: Dodaj kod implementacji w tym miejscu.
}

void Instance::eventPoll()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed: { window.close(); break; }
		}
	}
}

void Instance::keyboardInput()
{
	keyboardState = none;
	switch (instanceState)
	{
	case mainmenu: { keyboardState = static_cast<KeyboardState>(mainMenu.keyboardInput()); break; }
	case difficult: { keyboardState = static_cast<KeyboardState>(difficultMenu.keyboardInput()); break; }
	case highscores: { keyboardState = static_cast<KeyboardState>(scoresMenu.keyboardInput()); break; }
	case about: { keyboardState = static_cast<KeyboardState>(aboutMenu.keyboardInput()); break; }
	case gameLaunched: { keyboardState = static_cast<KeyboardState>(actualGame->keyboardInput()); break; }
	case gamePaused: { keyboardState = static_cast<KeyboardState>(pauseMenu.keyboardInput()); break; }
	case gameOver: { if (!isEntering) { keyboardState = static_cast<KeyboardState>(gameOverMenu.keyboardInput()); } break; }
	}
}

void Instance::refresh()
{
	switch (instanceState)
	{
	case splashscreen: { wait(1500); instanceState = mainmenu; break; }
	case mainmenu:
	{
		switch (keyboardState)
		{
		case 1: { instanceState = difficult; wait(100); break; }
		case 2: { instanceState = highscores; scoreControl.loadFromFile(false); wait(100); break; }
		case 3: { instanceState = about; wait(100); break; }
		case 4: { window.close(); break; }
		}
		break;
	}
	case difficult:
	{
		switch (keyboardState)
		{
		case 1: { instanceState = gameLaunched; actualGame = std::make_unique<Game>(instanceArea, false); wait(100); break; }
		case 2: { instanceState = gameLaunched; actualGame = std::make_unique<Game>(instanceArea, true); wait(100); break; }
		case 3: { instanceState = mainmenu; wait(200); break; }
		}
		break;
	}
	case highscores:
	{
		switch (keyboardState) 
		{ 
		case 1: { instanceState = mainmenu; wait(200); break; } 
		case -1: { scoresMenu.addition({ "Classic" }, instanceArea, { 658, 294 }); scoreControl.loadFromFile(false); wait(100); break; }
		case -2: { scoresMenu.addition({ "Endurance" }, instanceArea, { 658, 294 }); scoreControl.loadFromFile(true); wait(100); break; }
		}
		break;
	}
	case about:
	{
		switch (keyboardState) { case 1: { instanceState = mainmenu; wait(200); break; } }
		break;
	}
	case gameLaunched:
	{
		switch (keyboardState)
		{
		case none: 
		{ 
			actualGame->doLoop(enemyCooldown);
			if (actualGame->checkConditions())
			{
				lastScore = actualGame->getActualScore();
				bestScore = actualGame->getBestScore();
				if (actualGame->checkHiScores(0)) { isEntered = false; } 
				instanceState = gameOver;
			}
			break; 
		}
		case pausemenu: { instanceState = gamePaused; wait(100); break; }
		}
		break;
	}
	case gamePaused:
	{
		switch (keyboardState)
		{
		case 1: { instanceState = gameLaunched; wait(200); break; }
		case 2: { actualGame.reset(); instanceState = mainmenu; wait(200); break; }
		}
		break;
	}
	case gameOver:
	{
		if (actualGame->checkHiScores(0)) 
		{
			gameOverMenu.addition({ "Congratulations! You have a high score", "Enter your nickname:", "", "Your score: " + std::to_string(lastScore), "Best score: " + std::to_string(bestScore) }, instanceArea, { 658,272 });
			if (isEntered) 
			{ 
				actualGame->checkHiScores(1, nicknameInput); 
				switch (keyboardState)
				{
				case 1: { actualGame.reset(); instanceState = difficult; wait(200); break; }
				case 2: { actualGame.reset(); instanceState = mainmenu; wait(200); break; }
				}
			}
			else { isEntering = true; wait(60); prepareText(); }
		}
		else
		{
			gameOverMenu.addition({ "Your score: " + std::to_string(lastScore), "Best score: " + std::to_string(bestScore) }, instanceArea, { 658,416 });
			switch (keyboardState)
			{
			case 1: { actualGame.reset(); instanceState = difficult; wait(200); break; }
			case 2: { actualGame.reset(); instanceState = mainmenu; wait(200); break; }
			}
		}
		break;
	}
	}
}

void Instance::render()
{
	window.clear(backgroundColor);
	switch (instanceState)
	{
	case splashscreen: { /*window.draw(backgroundArea);*/ break; }
	case mainmenu: { window.draw(mainMenu); break; }
	case difficult: { window.draw(difficultMenu); break; }
	case highscores:
	{
		window.draw(scoresMenu);
		for (uint it = 1; it < 6; it++) { window.draw(scoreControl.getScore(it)); }
		break;
	}
	case about: { window.draw(aboutMenu); break; }
	case gameLaunched: { window.draw(*(actualGame.get())); break; }
	case gamePaused: { window.draw(pauseMenu); break; }
	case gameOver:
	{
		window.draw(gameOverMenu);
		if(!isEntered) { window.draw(nicknameText); }
		break;
	}
	}
	window.display();
}

void Instance::wait(unsigned int mseconds)
{
	sf::Time pause = sf::Time::Zero;
	sf::Clock clock;
	while (static_cast<uint>(pause.asMilliseconds()) < mseconds) { pause += clock.getElapsedTime(); clock.restart(); }
}

bool Instance::count(unsigned int mseconds)
{
	if (!startCounting) { countTime = sf::Time::Zero; startCounting = true; }
	sf::Clock clock;
	if (static_cast<uint>(countTime.asMilliseconds()) < mseconds) { countTime += clock.getElapsedTime(); clock.restart(); return false; }
	else { startCounting = false; return true; }
}

void Instance::prepareText()
{
	sf::Event event;
	nicknameText.setFont(font);
	nicknameText.setCharacterSize(36);
	nicknameText.setFillColor(fillColor);
	nicknameText.setPosition(640, 368);
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed: { window.close(); break; }
		case sf::Event::TextEntered: 
		{
			if ((event.text.unicode > 32) && (event.text.unicode < 128)) { nicknameInput += static_cast<char>(event.text.unicode); }
			else if (event.text.unicode == 8) { if (nicknameInput.getSize() > 0) { nicknameInput.erase(nicknameInput.getSize() - 1); } }
			else if (event.text.unicode == 13) { isEntered = true; isEntering = false; wait(200); }
			nicknameText.setString(nicknameInput);
			sf::FloatRect nicknameRect = nicknameText.getLocalBounds();
			nicknameText.setOrigin(nicknameRect.left + nicknameRect.width / 2, 0);
			break;
		}
		}
	}
	keyboardState = none;
}

void Instance::additions()
{
	sf::Image icon;
	icon.loadFromFile("assets/icon.ico");
	window.setIcon(16, 16, icon.getPixelsPtr());
	font.loadFromFile("assets/CubicCoreMono.ttf");
	difficultMenu.addition({ "Choose a difficulty:" }, instanceArea, { 658, 472 });
	scoresMenu.addition({ "Classic" }, instanceArea, { 658, 294 });
	aboutMenu.addition({ "SpaceInversers (2020) by Ciachociech", "This game is heavily-based on Space Invaders Game", "One major difference is shooting to enemies by satellite on the top of screen", "keyboard (in menu): W/NumPad8, S/NumPad2 - go to the previous/next option", "Enter/NumPad5 - choose selected option, Escape - go to the last option", "keyboard (in game): W/NumPad5 - shooting, A - moving left, D - moving right", "Escape/Backspace - go to pause menu", "I'm open for your opinion and suggestions! Let's enjoy and have fun!" }, instanceArea, { 658,224 });
	scoresMenu.changeAddMode();
	difficultMenu.changeAddMode();
	gameOverMenu.changeAddMode();
	aboutMenu.changeAddMode();
}