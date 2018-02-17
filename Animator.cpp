#include "Animator.h"
#include "GameClock.h"

Animator::~Animator(){ }

void Animator::addAnimation(string name, Animation * animation) {
	_animations.insert(pair<string, Animation*>(name, animation));
}

void Animator::setCurentAnimation(string name) {
	_currentAnimation = _animations[name];
	_sprite->setTextureRect(_currentAnimation->getRect());
}

void Animator::playAnimation() {

	_timeElapsed += GameClock::getInstance()->getElapsedTime();

	if (_timeElapsed > _currentAnimation->getTimeBetweenFrame()) {
		_currentAnimation->nextFrame();
		_timeElapsed = 0;
	}

	if (_currentAnimation) {
		_sprite->setTextureRect(_currentAnimation->getRect());
	}
}
