#ifndef FANTOMINFO_H
#define FANTOMINFO_H

#include<SFML\Graphics.hpp>

class FantomInfo{
public:
	sf::Vector2<int> direction;

	FantomInfo() { direction = sf::Vector2<int>(0, 0); }
	~FantomInfo() { }

	void reset() { direction = sf::Vector2<int>(0, 0);}
};

#endif