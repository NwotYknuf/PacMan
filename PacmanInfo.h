#ifndef PACMANINFO_H
#define PACMANINFO_H

#include<SFML\Graphics.hpp>

class PacmanInfo{
public:
	int score;
	sf::Vector2<int> direction;
	bool alive;

	PacmanInfo() { score = 0; direction = sf::Vector2<int>(0, 0); alive = true; }
	~PacmanInfo() { }

	void reset() { score = 0; direction = sf::Vector2<int>(0, 0); alive = true; }
};

#endif