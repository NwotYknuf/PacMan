#include "DrawCharacter.h"

template<>
bool DrawCharacter < unsigned, Vertice<sf::Vector2<int>>*>
::draw(const Character<unsigned, Vertice<sf::Vector2<int>>*>* character) {
	int h = _charSprite->getLocalBounds().height;
	int w = _charSprite->getLocalBounds().width;

	_charSprite->setPosition(character->position->value.x * w, character->position->value.y * h);
	_window->draw(*_charSprite);

	return true;
}