#include "Random.h"

Random * Random::_instance = NULL;

Random::Random() {
	_generator = &std::default_random_engine(165516);
}

Random * Random::getInstance(){
	if (!_instance) {
		_instance = new Random();
	}

	return _instance;
}

int Random::getNextRandom(int min, int max){
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(*_generator);
}
