#ifndef DRAWCHARACTER_H
#define DRAWCHARACTER_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Vertice.h"
#include "Character.h"

template<class Info, class Position>
class DrawCharacter {
private:

	sf::Sprite * _charSprite;
	sf::RenderWindow *_window;
	
public :

	DrawCharacter(sf::RenderWindow *window, sf::Sprite * charSprite);
	bool draw(const Character<Info, Position>* character);
};

template<class Info, class Position>
DrawCharacter<Info, Position>::DrawCharacter(sf::RenderWindow * window, sf::Sprite * charSprite){
	_window = window;
	_charSprite = charSprite;
}

#endif
