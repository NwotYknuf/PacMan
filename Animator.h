#pragma once
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

	void addAnnimation(string name, Animation* animation);

	void setCurentAnimation(string name);

	void playAnnimation();

};
