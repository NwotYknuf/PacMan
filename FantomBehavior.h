#pragma once
#include <SFML\Graphics.hpp>
#include <random>
#include "GCharacter.h"
#include "Graph.h"
#include "VerticeInfo.h"
#include "AStarTools.h"
#include "AStar.h"
#include "Random.h"
#include <vector>

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

	static Vertice<Vinfo> * vue(GCharacter<Vinfo, Einfo, Cinfo> * fantom);

	static Vertice<Vinfo> * flair(GCharacter<Vinfo, Einfo, Cinfo> * fantom);

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

/*
Vertice<VerticeInfo> * FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::vue(
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo> * fantom) {
	PElement<Vertice<VerticeInfo>> * voisins = new PElement<Vertice<VerticeInfo>>(0, 0);
	voisins->copy(fantom->graph->neighbors(fantom->position));
	sf::Vector2<int> v;
	sf::Vector2<int> v2;

	for (int i = 0; i < voisins->size; i++) {
		v = sf::Vector2<int>(voisins->value->value.info.pos.x - fantom->position->value.info.pos.x, voisins->value->value.info.pos.y - fantom->position->value.info.pos.y);
		Vertice<VerticeInfo> * parcours = voisins->value;

		while (parcours != NULL) {
			if (parcours->value.info.pacmanIsHere)
				return voisins->value;
			else
				PElement<Vertice<VerticeInfo>> * voisinsParcours = new PElement<Vertice<VerticeInfo>>(0, 0);
				voisinsParcours->copy(fantom->graph->neighbors(parcours));
				bool trouve = false;
				for (int j = 0; i < voisinsParcours->size; j++) {
					v2 = sf::Vector2<int>(voisinsParcours->value->value.info.pos.x - voisins->value->value.info.pos.x, voisinsParcours->value->value.info.pos.y - voisins->value->value.info.pos.y);
					if (v == v2) {
						trouve = true;
						parcours = voisinsParcours->value;
						break;
					}
					else {
						voisinsParcours->next;
					}
				}
				if (!trouve)
					parcours = NULL;
		}
		voisins->next;
	}
	return flair(fantom);
}
*/

/*
Vertice<VerticeInfo> * FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::flair(
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo> * fantom) {


}
*/
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
