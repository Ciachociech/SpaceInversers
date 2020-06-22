#include "Menu.h"

Menu::Menu(std::vector<std::string> textVector, sf::IntRect& menuArea, bool drawSprite, std::string filepath, uint width) : font(), textCollection(), fillColor(sf::Color(240, 240, 240, 255)), menuArea(menuArea), drawSprite(drawSprite)
{
	uint i = 0;
	if (textVector[0] == "") { skipFirstLine = true; i++; }
	load();
	menuTexture.loadFromFile(filepath, sf::IntRect(0, 0, 1280, width));
	menuSprite.setTexture(menuTexture);
	for (i; i < textVector.size(); i++)
	{
		textCollection.push_back(std::make_unique<sf::Text>(textVector[i], font));
		auto actualText = textCollection.begin() + (skipFirstLine?i-1:i);
		(*actualText)->setFillColor(fillColor);
		refreshPosition();
	}
}

Menu::Menu(std::vector<std::string> textVector, sf::IntRect& menuArea, bool drawSprite, std::string title) : font(), textCollection(), fillColor(sf::Color(240, 240, 240, 255)), menuArea(menuArea), drawSprite(drawSprite)
{
	uint i = 0;
	if (textVector[0] == "") { skipFirstLine = true; i++; titleText.setString(title); }
	load();
	for (i; i < textVector.size(); i++)
	{
		textCollection.push_back(std::make_unique<sf::Text>(textVector[i], font));
		auto actualText = textCollection.begin() + (skipFirstLine ? i - 1 : i);
		(*actualText)->setFillColor(fillColor);
		refreshPosition();
	}
}

Menu::~Menu() {}

void Menu::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	if (drawSprite) { Target.draw(menuSprite, States); }
	else { Target.draw(titleText, States); }
	for (auto& it : textCollection) { Target.draw(*it, States); }
	Target.draw(pointer, States);
	if (showAddText) { for (auto& it : additionalText) { Target.draw(*it, States); } }
}

void Menu::load() 
{ 
	if (!fontLoaded) { font.loadFromFile("assets/CubicCoreMono.ttf"); fontLoaded = true; }
	pointer.setString("=>");
	pointer.setFont(font);
	pointer.setCharacterSize(24);
	if (skipFirstLine)
	{
		titleText.setFont(font);
		titleText.setCharacterSize(160);
		sf::FloatRect titleRect = titleText.getLocalBounds();
		titleText.setOrigin(titleRect.width / 2, 0);
		titleText.setPosition(640, 32);
		titleText.setFillColor(fillColor);
	}
}

void Menu::refreshPosition()
{
	for (unsigned int i = 0; i < textCollection.size(); i++)
	{
		auto actualText = textCollection.begin() + i;
		(*actualText)->setPosition(580.0, static_cast<float>(668.0 - 48.0 * textCollection.size() + 48.0 * i));
	}
	pointer.setPosition(540.0, static_cast<float>(668.0 - 48.0 * textCollection.size() + 48.0 * pointerState));
}

int Menu::keyboardInput()
{
	if (chosen) { pointerState = 0; chosen = false; }
	keyPause += clock.getElapsedTime();
	clock.restart();
	if (keyPause.asMilliseconds() >= 350)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) { if (pointerState > 0) { pointerState -= 1; keyPause = sf::Time::Zero; } }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) { if (pointerState < textCollection.size() - 1) { pointerState += 1; keyPause = sf::Time::Zero; } }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { return -1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { return -2; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) { chosen = true; return static_cast<int>(pointerState += 1); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { pointerState = static_cast<uint>(textCollection.size() - 1); keyPause = sf::Time::Zero; }
	refreshPosition();
	return 0;
}

void Menu::addition(std::vector<std::string> textVector, sf::IntRect& menuArea, sf::Vector2f coord)
{
	additionalText.clear();
	for (uint i=0; i < textVector.size(); i++)
	{
		additionalText.push_back(std::make_unique<sf::Text>(textVector[i], font, 36));
		auto actualText = additionalText.begin() + i;
		(*actualText)->setFillColor(fillColor);
		if ((coord.x == 0) && (coord.y == 0)) { (*actualText)->setPosition(640.0, static_cast<float>(256.0 + 48.0 * i)); }
		else { (*actualText)->setPosition(coord.x, static_cast<float>(coord.y + 48.0 * i)); }
		sf::FloatRect additRect = (*actualText)->getLocalBounds();
		(*actualText)->setOrigin(additRect.top + additRect.width / 2, 0);
	}
}

void Menu::changeAddMode() 
{ 
	if (showAddText) { showAddText = false; }
	else { showAddText = true; }
}