#include "Animator.h"
#include "GameClock.h"

Animator::~Animator(){ }

void Animator::addAnimation(string name, Animation * animation) {
	_animations.insert(pair<string, Animation*>(name, animation));
}

void Animator::setCurentAnimation(string name) {
	_currentAnimation = _animations[name];
}

void Animator::update() {

	for (pair<string, Animation*> p : _animations)	{
		p.second->update();
	}
}

void Animator::reset(){

	for (pair<string, Animation*> p : _animations) {
		p.second->reset();
	}

}

void Animator::playAnimation() {
	
	if (_currentAnimation) {
		_sprite->setTextureRect(_currentAnimation->getRect());
	}

}
