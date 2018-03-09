#ifndef FANTOMBEHAVIOR_H
#define FANTOMBEHAVIOR_H

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

	static Vertice<Vinfo> * sight(GCharacter<Vinfo, Einfo, Cinfo> * fantom);

	static Vertice<Vinfo> * scent(GCharacter<Vinfo, Einfo, Cinfo> * fantom);

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

template<>
Vertice<VerticeInfo> * FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::sight(
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo> * fantom) {
	//TODO delete lists properly

	PElement<Vertice<VerticeInfo>> * voisins = fantom->graph->neighbors(fantom->position);
	Vertice<VerticeInfo> * parcours;
	sf::Vector2<int> direction;
	sf::Vector2<int> diff;
	
	while(voisins != NULL) {
		Vertice<VerticeInfo> * v = voisins->value;
		parcours = v;

		direction = sf::Vector2<int>(
			parcours->value.info.pos.x - fantom->position->value.info.pos.x,
			parcours->value.info.pos.y - fantom->position->value.info.pos.y);

		while (parcours != NULL) {
			if (parcours->value.info.pacmanIsHere) {
				return v;
			}
			else {
				PElement<Vertice<VerticeInfo>> * voisinsParcours = fantom->graph->neighbors(parcours);
				bool trouve = false;

				while(voisinsParcours != NULL) {
					diff = sf::Vector2<int>(
						voisinsParcours->value->value.info.pos.x - parcours->value.info.pos.x,
						voisinsParcours->value->value.info.pos.y - parcours->value.info.pos.y);

					if (direction == diff) {
						trouve = true;
						parcours = voisinsParcours->value;
					}
					else {
						voisinsParcours = voisinsParcours->next;
					}
				}
				if (!trouve)
					parcours = NULL;
			}
		}
		voisins = voisins->next;
	}
	
	return scent(fantom);
}


template<>
Vertice<VerticeInfo> * FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::scent(
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo> * fantom) {
	//TODO delete lists properly
	PElement<Edge<EdgeInfo, VerticeInfo>>* neighbors = fantom->graph->adjacentEdges(fantom->position);

	Vertice<VerticeInfo> * target = NULL;
	float highestHeatYet = 0.0f;

	while (neighbors != NULL) {
		if (neighbors->value->value.heat > highestHeatYet) {
			target = fantom->position == neighbors->value->begin ? neighbors->value->end : neighbors->value->begin;
		}
		neighbors = neighbors->next;
	}

	return target==NULL ? random(fantom) : target;
}

template<class Vinfo, class Einfo, class Cinfo>
const float FantomBehavior<Vinfo, Einfo, Cinfo>::UPDATE_RATE = 0.25f;

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

#endif