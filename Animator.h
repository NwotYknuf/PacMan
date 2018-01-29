#ifndef ANIMATOR_H
#define ANIMATOR_H

#include<map>
#include "Animation.h"

using namespace std;

class Animator{
private:
	map<string, Animation*> _animations;
	Animation * _currentAnimation;

public:
	Animator();
	~Animator();

	void addAnimation(string name, Animation* animation);

	void setCurentAnimation(string name);

	void playAnnimation();

};

#endif // !ANIMATOR_H
