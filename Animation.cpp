#include "Animation.h"
#include "GameClock.h"

Animation::Animation(float timeBetweenFrames, bool loop){
	_loop = loop;
	_currentFrame = 0;
	_timeBetweenFrames = timeBetweenFrames;
}

Animation::~Animation(){ }

void Animation::addFrame(const sf::IntRect &rect){
	_frames.push_back(rect);
}

void Animation::nextFrame() {

	_currentFrame++;

	if (_currentFrame > _frames.size() - 1) {
		if (_loop)
			_currentFrame = 0;
		else
			_currentFrame = _frames.size() - 1;
	}

}

void Animation::update() {
	_timeElapsed += GameClock::getInstance()->getElapsedTime();

	if (_timeElapsed > _timeBetweenFrames) {
		nextFrame();
		_timeElapsed -= _timeBetweenFrames;
	}
	
}

void Animation::reset() {
	_currentFrame = 0;
}
