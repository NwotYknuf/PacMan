#ifndef RANDOM_H
#define RANDOM_H
#include <random>

class Random {
private:
	std::default_random_engine *_generator;
	static Random * _instance;
	Random();

public:
	static Random * getInstance();
	int getNextRandom(int min, int max);
	~Random() { };
};

#endif
