#ifndef INFORMATIONS_H
#define INFORMATIONS_H

#include <iostream>
#include <SFML\Graphics.hpp>


using namespace std;

class Informations {

public :

	sf::Vector2<int> pos;
	bool pacmanIsHere;
	bool pacGom;
	
	Informations(const sf::Vector2<int> &v, bool p = true) : pos(v), pacGom(p) {
		pacmanIsHere = false;
	}

	friend ostream& operator <<(ostream &os, const Informations &info) {

		os << "{ position : (" << info.pos.x << ", " << info.pos.y << ") Pacman is here :";

		if (info.pacmanIsHere)
			os << "yes";
		else
			os << "no";
		os << ", is there a pacGom :";
		if (info.pacGom)
			os << "yes";
		else
			os << "no";
		os << " }";
		return os;
	}

};

#endif