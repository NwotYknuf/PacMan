#ifndef ACTOR_H
#define ACTOR_H

#include "Vertice.h"

template<class Character, class Behavior, class Draw>
class Actor{
private:
	Character * _character;
	Behavior * _behavior;
	Draw * _draw;

public:
	Actor() = delete;
	Actor(Character * character, Behavior * behavior, Draw * draw);
	~Actor();

	template<class Vinfo>
	void setBehavior(Vertice<Vinfo>* (*nextMove)(Character * fantom));
	void setLastInput(sf::Keyboard::Key key) { _behavior->setLastInput(key); }
	void setAnimation(string name) { _draw->setAnimation(name); }
	template<class Vinfo>
	Vertice<Vinfo> * getPosition() { return _character->position; }

	Character * getGchar() { return _character; }

	void update();	
	void updateEndGame();
	void reset();
	void resetAnimator();
};

template<class Character, class Behavior, class Draw>
Actor<Character, Behavior, Draw>::Actor(Character * character, Behavior * behavior, Draw * draw){
	_character = character;
	_behavior = behavior;
	_draw = draw;
}

template<class Character, class Behavior, class Draw>
Actor<Character, Behavior, Draw>::~Actor(){ }

template<class Character, class Behavior, class Draw>
template<class Vinfo>
void Actor<Character, Behavior, Draw>::setBehavior(Vertice<Vinfo>*(*nextMove)(Character *fantom)) {
	_behavior->setBehavior(nextMove);
}

template<class Character, class Behavior, class Draw>
void Actor<Character, Behavior, Draw>::update() {
	_character->update(*_behavior);
	_draw->update();
	_character->drawCharacter(*_draw);
}

template<class Character, class Behavior, class Draw>
void Actor<Character, Behavior, Draw>::updateEndGame() {
	_draw->update();
	_character->drawCharacter(*_draw);
}

template<class Character, class Behavior, class Draw>
void Actor<Character, Behavior, Draw>::reset(){
	_character->reset();
}

template<class Character, class Behavior, class Draw>
void Actor<Character, Behavior, Draw>::resetAnimator() {
	_draw->reset();
}

#endif
