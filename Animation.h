#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>

class Animation{
private:
	std::vector<sf::IntRect> _frames;
	float _timeBetweenFrames;
	int _currentFrame;

public:
	Animation(float timeBetweenFrames);
	~Animation();
	void addFrame(const sf::IntRect &rect);
	float getTimeBetweenFrame() { return _timeBetweenFrames; }
	void nextFrame();
	sf::IntRect& getRect() { return _frames[_currentFrame]; }
};

#endif
