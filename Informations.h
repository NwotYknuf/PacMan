#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>


using namespace std;

class Informations {

public :

	sf::Vector2<int> pos;
	bool pacmanIsHere;
	
	Informations(const sf::Vector2<int> &v) : pos(v) {
		pacmanIsHere = false;
	}

	friend ostream& operator <<(ostream &os, const Informations &info) {

		os << "position : (" << info.pos.x << ", " << info.pos.y << ")" << endl;
		if (info.pacmanIsHere)
			os << " Pacman is here";
		return os;
	}

};