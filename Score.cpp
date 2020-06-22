#include "Score.h"

Score::Score(std::string nickname, uint points, bool isActual) : nickname(nickname), points(points), isActual(isActual), isInGame(false), showPts(points), fillColor(sf::Color(240, 240, 240, 255)) { load(); }

Score::~Score() {}

void Score::addPoints(int pts) { points += pts; showPts = points; load(); }

void Score::reset() 
{ 
	nickname = "";
	points = 0;
	load();
}

void Score::load()
{
	if (!fontLoaded) { font.loadFromFile("assets/CubicCoreMono.ttf"); fontLoaded = true; }
	if (!isInGame) 
	{ 
		scoreNickname.setString(nickname); scorePoints.setString(std::to_string(points));
		sf::FloatRect scoreNickRect = scoreNickname.getLocalBounds(), scorePtsRect = scorePoints.getLocalBounds();
		scoreNickname.setOrigin(0, 0);
		scorePoints.setOrigin(scorePtsRect.left + scorePtsRect.width, 0);
	}
	else 
	{
		scoreNickname.setString("");
		if (isActual) { scorePoints.setString("score: " + std::to_string(points)); }
		else { scorePoints.setString("hi-score: " + std::to_string(showPts)); }
		sf::FloatRect scorePtsRect = scorePoints.getLocalBounds();
		scorePoints.setOrigin(scorePtsRect.left + scorePtsRect.width / 2, 0);
	}
	scoreNickname.setFont(font); scorePoints.setFont(font);
	scoreNickname.setCharacterSize(36); scorePoints.setCharacterSize(36);
	scoreNickname.setFillColor(fillColor); scorePoints.setFillColor(fillColor);
}

void Score::draw(sf::RenderTarget& Target, sf::RenderStates States) const 
{ 
	Target.draw(scoreNickname, States); Target.draw(scorePoints, States);
}

std::string Score::getNickname() { return nickname; }

uint Score::getPoints() { return points; }

void Score::changeScoreMode()
{ 
	if (isInGame) { isInGame = false; }
	else { isInGame = true; }
	load();
}

void Score::refreshPosition(uint order)
{
	switch (order)
	{
	case 0: { if (isInGame) { scorePoints.setPosition(520, 16); } break; }
	case 1: 
	{ 
		if (isInGame) { scorePoints.setPosition(760, 16); } 
		else { scoreNickname.setPosition(400, 344); scorePoints.setPosition(880 - scorePoints.getLocalBounds().width, 344); }
		break;
	}
	case 2: { scoreNickname.setPosition(400, 392); scorePoints.setPosition(880 - scorePoints.getLocalBounds().width, 392); break; }
	case 3: { scoreNickname.setPosition(400, 440); scorePoints.setPosition(880 - scorePoints.getLocalBounds().width, 440); break; }
	case 4: { scoreNickname.setPosition(400, 488); scorePoints.setPosition(880 - scorePoints.getLocalBounds().width, 488); break; }
	case 5: { scoreNickname.setPosition(400, 536); scorePoints.setPosition(880 - scorePoints.getLocalBounds().width, 536); break; }
	}
}

std::string Score::hiScoreString() 
{
	std::string buffer = nickname, insert = buffer;
	insert.append(24 - buffer.size(), ' ');
	buffer = std::to_string(points);
	insert.append(12 - buffer.size(), ' ');
	return insert + buffer;
}

void Score::showPoints(uint pts) { showPts = pts; load(); }

void Score::setNickname(std::string nick) { nickname = nick; }