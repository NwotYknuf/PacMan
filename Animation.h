#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>

class Animation{
private:
	std::vector<sf::IntRect> _frames;
	float _timeBetweenFrames;
	bool _loop;
	int _currentFrame;

	float _timeElapsed = 0;

public:
	Animation(float timeBetweenFrames, bool loop = true);
	~Animation();
	void addFrame(const sf::IntRect &rect);
	float getTimeBetweenFrame() { return _timeBetweenFrames; }
	void nextFrame();
	void update();
	void reset();
	sf::IntRect& getRect() { return _frames[_currentFrame]; }
};

#endif
