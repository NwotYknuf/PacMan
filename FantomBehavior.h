#pragma once
#include <SFML\Graphics.hpp>
#include <random>
#include "GCharacter.h"
#include "Graph.h"
#include "VerticeInfo.h"
#include "AStarTools.h"
#include "AStar.h"
#include "Random.h"

template <class Vinfo, class Einfo, class Cinfo>
class FantomBehavior {
private:
	float _timeElapsed = 0.0f;
	Vertice<Vinfo>* (*_nextMove)(GCharacter<Vinfo, Einfo, Cinfo> * fantom);

	const static float UPDATE_RATE;

public:
	FantomBehavior() = delete;

	FantomBehavior(Vertice<Vinfo>* (*nextMove)(GCharacter<Vinfo, Einfo, Cinfo> * fantom)) {
		_nextMove = nextMove;
	}

	~FantomBehavior() { }

	void update(GCharacter<Vinfo, Einfo, Cinfo> * fantom);

	static Vertice<Vinfo> * aStar(GCharacter<Vinfo, Einfo, Cinfo> * fantom);

	static Vertice<Vinfo> * random(GCharacter<Vinfo, Einfo, Cinfo> * fantom);

};

template<>
Vertice<VerticeInfo> * FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::aStar(	
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo> * fantom){

	Vertice<VerticeInfo> * result = NULL;
	result = AStar<Graph<EdgeInfo, VerticeInfo>, Vertice<VerticeInfo>>::aStar(*fantom->graph, fantom->position, AStarTools::computeHeuristic);
	result = penultimateElement(result);

	return result;
}

template<>
Vertice<VerticeInfo> * FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::random(
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo> * fantom) {

	PElement<Vertice<VerticeInfo>> * neighbors = fantom->graph->neighbors(fantom->position);

	int n = neighbors->size(neighbors);
	
	for (int i = 0; i < Random::getInstance()->getNextRandom(0, n-1); i++){
		neighbors = neighbors->next;
	}

	return neighbors->value;
}

template<class Vinfo, class Einfo, class Cinfo>
const float FantomBehavior<Vinfo, Einfo, Cinfo>::UPDATE_RATE = 0.2f;

template<class Vinfo, class Einfo, class Cinfo>
void FantomBehavior<Vinfo, Einfo, Cinfo>::update(
	GCharacter<Vinfo, Einfo, Cinfo>* fantom) {

	_timeElapsed += GameClock::getInstance()->getElapsedTime();

	if (_timeElapsed > UPDATE_RATE) {
		Vertice<Vinfo> * nextMove = _nextMove(fantom);

		if (!fantom->move(nextMove)) {
			fantom->updateInfosFailure();
		}

		_timeElapsed -= UPDATE_RATE;
	}
}
