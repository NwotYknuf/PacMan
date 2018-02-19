#pragma once
#include<SFML\Graphics.hpp>

class PacmanInfo{
public:
	int score;
	sf::Vector2<int> direction;

	PacmanInfo() { score = 0; direction = sf::Vector2<int>(0, 0); }

	~PacmanInfo() { }
};

