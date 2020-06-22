#pragma once

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

typedef unsigned int uint;

class Score : public sf::Drawable
{
private:
	std::string nickname;
	uint points, showPts;
	bool isInGame, isActual, fontLoaded = false;
	
	sf::Font font;
	sf::Text scoreNickname, scorePoints;
	sf::Color fillColor;

	void load();
public:
	Score(std::string nickname, uint points, bool isActual);
	~Score();

	void addPoints(int pts);
	void reset();
	void draw(sf::RenderTarget& Target, sf::RenderStates States) const;
	void changeScoreMode();
	void refreshPosition(uint position);

	std::string getNickname();
	void setNickname(std::string nick);
	uint getPoints();
	void showPoints(uint pts);
	
	std::string hiScoreString();
};

typedef std::unique_ptr<Score> Score_uptr;