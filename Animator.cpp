#include "Animator.h"

Animator::Animator(){ }

Animator::~Animator(){ }

void Animator::addAnimation(string name, Animation * animation) {
	_animations.insert(pair<string, Animation*>(name, animation));
}

void Animator::setCurentAnimation(string name) {
	_currentAnimation = _animations[name];
}

void Animator::playAnnimation() {
	if (_currentAnimation)
		_currentAnimation->playAnnimation();
}
