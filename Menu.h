#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

typedef std::vector<std::unique_ptr<sf::Text>> VecText;
typedef std::vector<std::string> VecString;
typedef unsigned int uint;

class Menu : public sf::Drawable
{
private:
	sf::IntRect menuArea;
	sf::Font font;
	VecText textCollection, additionalText;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	sf::Time keyPause = sf::Time::Zero;
	sf::Clock clock;
	sf::Color fillColor;
	sf::Text pointer, titleText;

	bool drawSprite, fontLoaded = false, skipFirstLine, showAddText = false;
	uint fontSize = 18, pointerState = 0, chosen = false;

	void load();
	void refreshPosition();
public:
	Menu(std::vector<std::string> textVector, sf::IntRect& menuArea, bool drawSprite, std::string filepath, uint width);
	Menu(std::vector<std::string> textVector, sf::IntRect& menuArea, bool drawSprite, std::string title);
	~Menu();

	void draw(sf::RenderTarget& Target, sf::RenderStates States) const override;
	int keyboardInput();
	void addition(std::vector<std::string> textVector, sf::IntRect& menuArea, sf::Vector2f coords = {0,0});
	void changeAddMode();
};

