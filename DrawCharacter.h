#ifndef DRAWCHARACTER_H
#define DRAWCHARACTER_H

#include "Vertice.h"
#include "GCharacter.h"
#include "Animator.h"
#include "VerticeInfo.h"
#include "PacmanInfo.h"
#include "FantomInfo.h"
#include "Window.h"

template<class Vinfo, class Einfo, class Cinfo>
class DrawCharacter : public Window{
private:

	sf::Sprite * _charSprite;
	Animator * _animator;
	sf::Font * _font;
	
public :

	DrawCharacter(sf::RenderWindow *window, sf::Sprite * charSprite, Animator * animator, WorldToScreen worldToScreenTransform, sf::Font * font);

	bool draw(const GCharacter<Vinfo, Einfo, Cinfo>* character);

	void update();

};

template<class Vinfo, class Einfo, class Cinfo>
DrawCharacter<Vinfo, Einfo, Cinfo>::DrawCharacter(
	sf::RenderWindow * window, 	
	sf::Sprite * charSprite, 
	Animator * animator, 	
	WorldToScreen worldToScreenTransform, 
	sf::Font * font)
		: Window(window, worldToScreenTransform){
	_font = font;
	_charSprite = charSprite;
	_animator = animator;
}

template<>
bool DrawCharacter < VerticeInfo, EdgeInfo, PacmanInfo>
::draw(const GCharacter<VerticeInfo, EdgeInfo, PacmanInfo>* character) {
	//animation

	string str = "explode";

	if (character->info.alive) {
		str = character->info.direction == sf::Vector2<int>(0, 0) ? "standStill" : "walk";

		switch (character->info.direction.y) {
		case -1:
			str += "Down";
			break;
		case 1:
			str += "Up";
		}
		switch (character->info.direction.x) {
		case 1:
			str += "Right";
			break;
		case -1:
			str += "Left";
		}
	}

	_animator->setCurentAnimation(str);

	//placement
	sf::Vector2<float> screenCoord = _worldToScreenTransform(
		sf::Vector2<float>(character->position->value.info.pos.x, character->position->value.info.pos.y));

	_charSprite->setPosition(screenCoord.x, screenCoord.y);

	_animator->playAnimation();

	//zoom
	_charSprite->setOrigin(_charSprite->getLocalBounds().height / 2.0f, _charSprite->getLocalBounds().width / 2.0f);
	float zoomX = _worldToScreenTransform.zoom / _charSprite->getLocalBounds().width;
	float zoomY = _worldToScreenTransform.zoom / _charSprite->getLocalBounds().height;
	_charSprite->setScale(sf::Vector2<float>(zoomX, zoomY));

	_window->draw(*_charSprite);

	//score
	sf::Text text;
	char string[30];
	sprintf_s(string, "Score : %d", character->info.score);
	text.setString(string);
	text.setFillColor(sf::Color::Cyan);
	text.setFont(*_font);
	text.setPosition(_worldToScreenTransform(sf::Vector2<float>(-1, 0)));
	_window->draw(text);

	return true;
}

template<>
bool DrawCharacter < VerticeInfo, EdgeInfo, FantomInfo>
::draw(const GCharacter<VerticeInfo, EdgeInfo, FantomInfo>* character) {
	//animation
	string str = character->info.direction == sf::Vector2<int>(0, 0) ? "standStill" : "walk";

	switch (character->info.direction.y) {
	case -1:
		str += "Down";
		break;
	case 1:
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
	
	sf::Vector2<float> screenCoord = _worldToScreenTransform(
		sf::Vector2<float>(character->position->value.info.pos.x, character->position->value.info.pos.y));

	_charSprite->setPosition(screenCoord.x, screenCoord.y);

	_animator->playAnimation();

	//zoom
	_charSprite->setOrigin(_charSprite->getLocalBounds().height / 2.0f, _charSprite->getLocalBounds().width / 2.0f);
	float zoomX = _worldToScreenTransform.zoom / _charSprite->getLocalBounds().width;
	float zoomY = _worldToScreenTransform.zoom / _charSprite->getLocalBounds().height;
	_charSprite->setScale(sf::Vector2<float>(zoomX, zoomY));
	
	_window->draw(*_charSprite);
	
	return true;
}

template<class Vinfo, class Einfo, class Cinfo>
void DrawCharacter<Vinfo, Einfo, Cinfo>::update() {
	_animator->update();
}

#endif
