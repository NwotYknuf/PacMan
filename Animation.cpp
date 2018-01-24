#include "Animation.h"
#include "GameClock.h"

Animation::Animation(sf::Sprite *sprite, double timeBetweenFrames){
	_sprite = sprite;
	_currentFrame = 0;
	_timeBetweenFrames = timeBetweenFrames;
}

Animation::~Animation(){
}

void Animation::addFrame(const sf::IntRect &rect){
	_frames.push_back(rect);
}

void Animation::playAnnimation() {

	_timeElapsed += GameClock::getInstance()->getElapsedTime();

	if (_timeElapsed > _timeBetweenFrames) {

		_sprite->setTextureRect(_frames[_currentFrame]);
		_currentFrame++;

		if (_currentFrame >= _frames.size()) {
			_currentFrame = 0;
		}

		_timeElapsed = 0;
	}
}
