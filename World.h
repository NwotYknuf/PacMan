#ifndef WORLD_H
#define WORLD_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Actor.h"
#include "DrawGraph.h"
#include "GameClock.h"
#include "Graph.h"
#include "GCharacter.h"
#include "PacmanBehavior.h"
#include "FantomBehavior.h"
#include "DrawCharacter.h"

using namespace std;

class World {
private:

	Graph<EdgeInfo, VerticeInfo> * _graph;
	DrawGraph<EdgeInfo, VerticeInfo> * _drawGraph;

	Actor<
		GCharacter<VerticeInfo, EdgeInfo, PacmanInfo>,
		PacmanBehavior<VerticeInfo, EdgeInfo, PacmanInfo>,
		DrawCharacter<VerticeInfo, EdgeInfo, PacmanInfo>
	> * _pacman;

	vector<Actor<
		GCharacter<VerticeInfo, EdgeInfo, FantomInfo>,
		FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>,
		DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>
	> * > _fantoms;

	sf::RenderWindow * _window;
	sf::Font * font;
	WorldToScreen _transform;

	//game state
	static const float HEAT_DECAY;
	sf::Event event;
	bool end = false;
	int difficulty = 0;
	GameClock * clock;
	float elapsedTime = 0.0f;
	sf::Text gameOverText;
	sf::Text victoryText;

public:
	World(
		sf::RenderWindow * window,
		Graph<EdgeInfo, VerticeInfo> * graph,
		DrawGraph<EdgeInfo, VerticeInfo> * drawGraph,
		Actor<
		GCharacter<VerticeInfo, EdgeInfo, PacmanInfo>,
		PacmanBehavior<VerticeInfo, EdgeInfo, PacmanInfo>,
		DrawCharacter<VerticeInfo, EdgeInfo, PacmanInfo>
		> * pacman,
		sf::Font * _font,
		WorldToScreen &_transform);
	World() = delete;
	~World();

	void addFantom(Actor<
		GCharacter<VerticeInfo, EdgeInfo, FantomInfo>,
		FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>,
		DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>> *fantom);

	int nbrOfPacgoms();

	void init();
	void updateGraph();
	void handleEvents();
	void updateMain();
	void updateGameOver();
	void updateWin();
	void resetGraph();
	void resetGameOver();
	void resetVictory();
	void update();
	void setDifficulty(int diff);

};


#endif
