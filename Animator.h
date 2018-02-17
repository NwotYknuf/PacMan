#ifndef ANIMATOR_H
#define ANIMATOR_H

#include<map>
#include "Animation.h"

using namespace std;

class Animator{
private:
	sf::Sprite * _sprite;
	map<string, Animation*> _animations;
	Animation * _currentAnimation;

	float _timeElapsed = 0;

public:
	Animator(sf::Sprite * sprite) { _sprite = sprite; }
	~Animator();

	void addAnimation(string name, Animation* animation);

	void setCurentAnimation(string name);

	void playAnimation();

	void setSprite(sf::Sprite* sprite) { _sprite = sprite; }

};

#endif // !ANIMATOR_H
