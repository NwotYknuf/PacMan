#ifndef ACTOR_H
#define ACTOR_H

#include "GCharacter.h"
#include "FantomBehavior.h"
#include "PacmanInfo.h"
#include "FantomBehavior.h"
#include "PacmanBehavior.h"
#include "DrawCharacter.h"

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

	void update();
	void reset();
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
void Actor<Character, Behavior, Draw>::update() {
	_character->update(*_behavior);
	_draw->update();
	_character->drawCharacter(*_draw);
}

template<class Character, class Behavior, class Draw>
void Actor<Character, Behavior, Draw>::reset(){
	_character->reset();
}

#endif
