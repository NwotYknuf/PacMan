#ifndef DRAWCHARACTER_H
#define DRAWCHARACTER_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Vertice.h"
#include "Character.h"
#include "Animator.h"
#include "VerticeInfo.h"

template<class Info, class VerticeInformation>
class DrawCharacter {
private:

	sf::Sprite * _charSprite;
	Animator * _animator;
	sf::RenderWindow *_window;
	
public :

	DrawCharacter(sf::RenderWindow *window, sf::Sprite * charSprite, Animator * animator);
	bool draw(const GCharacter<Info, VerticeInformation>* character);
};

template<class Info, class VerticeInformation>
DrawCharacter<Info, VerticeInformation>::DrawCharacter(sf::RenderWindow * window, sf::Sprite * charSprite, Animator * animator){
	_window = window;
	_charSprite = charSprite;
	_animator = animator;
}

template<>
bool DrawCharacter < unsigned, VerticeInfo>
::draw(const GCharacter<unsigned, VerticeInfo>* character) {
	float h = _charSprite->getLocalBounds().height;
	float w = _charSprite->getLocalBounds().width;

	_charSprite->setPosition(character->position->value.info.pos.x * w, character->position->value.info.pos.y * h);

	_animator->playAnimation();
	_window->draw(*_charSprite);

	return true;
}

#endif
