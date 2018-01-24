#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>

class Animation{
private:
	std::vector<sf::IntRect> _frames;
	sf::Sprite *_sprite;
	int _currentFrame;
	float _timeBetweenFrames;
	float _timeElapsed;

public:
	Animation(sf::Sprite *sprite, double timeBetweenFrames);
	~Animation();
	void addFrame(const sf::IntRect &rect);
	void playAnnimation();

};

#endif
