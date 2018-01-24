#ifndef GAMECLOCK_H
#define GAMECLOCK_H
#include <SFML/System.hpp>


class GameClock {
private :
	sf::Clock * clock;
	GameClock();
	static GameClock * instance;
	
public :
	static GameClock * getInstance();
	float getElapsedTime();
	void restart();
	~GameClock() { };
};

#endif
