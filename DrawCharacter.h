#ifndef DRAWCHARACTER_H
#define DRAWCHARACTER_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Vertice.h"
#include "Character.h"

template<class Info, class VerticeInfo>
class DrawCharacter {
private:

	sf::Sprite * _charSprite;
	sf::RenderWindow *_window;
	
public :

	DrawCharacter(sf::RenderWindow *window, sf::Sprite * charSprite);
	bool draw(const Character<Info, VerticeInfo>* character);
};

template<class Info, class VerticeInfo>
DrawCharacter<Info, VerticeInfo>::DrawCharacter(sf::RenderWindow * window, sf::Sprite * charSprite){
	_window = window;
	_charSprite = charSprite;
}

template<>
bool DrawCharacter < unsigned, sf::Vector2<int>>
::draw(const Character<unsigned, sf::Vector2<int>>* character) {
	int h = _charSprite->getLocalBounds().height;
	int w = _charSprite->getLocalBounds().width;

	_charSprite->setPosition(character->position->value.x * w, character->position->value.y * h);
	_window->draw(*_charSprite);

	return true;
}

#endif
