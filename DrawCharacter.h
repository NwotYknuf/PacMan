#ifndef DRAWCHARACTER_H
#define DRAWCHARACTER_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Vertice.h"
#include "GCharacter.h"
#include "Animator.h"
#include "VerticeInfo.h"
#include "PacmanInfo.h"
#include "FantomInfo.h"

template<class Vinfo, class Einfo, class Cinfo>
class DrawCharacter {
private:

	sf::Sprite * _charSprite;
	Animator * _animator;
	sf::RenderWindow *_window;
	
public :

	DrawCharacter(sf::RenderWindow *window, sf::Sprite * charSprite, Animator * animator);

	bool draw(const GCharacter<Vinfo, Einfo, Cinfo>* character);

	void update();
};

template<class Vinfo, class Einfo, class Cinfo>
DrawCharacter<Vinfo, Einfo, Cinfo>::DrawCharacter(sf::RenderWindow * window, sf::Sprite * charSprite, Animator * animator){
	_window = window;
	_charSprite = charSprite;
	_animator = animator;
}

template<>
bool DrawCharacter < VerticeInfo, EdgeInfo, PacmanInfo>
::draw(const GCharacter<VerticeInfo, EdgeInfo, PacmanInfo>* character) {
	//animation
	string str = character->info.direction == sf::Vector2<int>(0, 0) ? "standStill" : "walk";

	switch (character->info.direction.y) {
		case 1:
			str += "Down";
			break;
		case -1:
			str += "Up";
	}
	switch (character->info.direction.x) {
	case 1:
		str += "Right";
		break;
	case -1:
		str += "Left";
	}

	_animator->setCurentAnimation(str);

	//placement
	float h = _charSprite->getLocalBounds().height;
	float w = _charSprite->getLocalBounds().width;

	_charSprite->setPosition(character->position->value.info.pos.x * w, character->position->value.info.pos.y * h);

	_animator->playAnimation();
	_window->draw(*_charSprite);

	return true;
}

template<>
bool DrawCharacter < VerticeInfo, EdgeInfo, FantomInfo>
::draw(const GCharacter<VerticeInfo, EdgeInfo, FantomInfo>* character) {
	//animation
	string str = character->info.direction == sf::Vector2<int>(0, 0) ? "standStill" : "walk";

	switch (character->info.direction.y) {
	case 1:
		str += "Down";
		break;
	case -1:
		str += "Up";
	}
	switch (character->info.direction.x) {
	case 1:
		str += "Right";
		break;
	case -1:
		str += "Left";
	}

	_animator->setCurentAnimation(str); 
	
	float h = _charSprite->getLocalBounds().height;
	float w = _charSprite->getLocalBounds().width;

	_charSprite->setPosition(character->position->value.info.pos.x * w, character->position->value.info.pos.y * h);

	_animator->playAnimation();
	_window->draw(*_charSprite);

	return true;
}

template<class Vinfo, class Einfo, class Cinfo>
void DrawCharacter<Vinfo, Einfo, Cinfo>::update() {
	_animator->update();
}

#endif
