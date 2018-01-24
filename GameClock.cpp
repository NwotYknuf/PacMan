#include "GameClock.h"

GameClock * GameClock::instance = NULL;

GameClock * GameClock::getInstance() {
	if (!instance) {
		instance = new GameClock;
	}
	return instance;
}

GameClock::GameClock() {
	clock = new sf::Clock;
}

float GameClock::getElapsedTime() {
	return clock->getElapsedTime().asSeconds();
}

void GameClock::restart() {
	clock->restart();
}
