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
	PElement<Vertice<VerticeInfo>> * temp = neighbors;
	
	int n = temp->size(temp);
	
	for (int i = 0; i < Random::getInstance()->getNextRandom(0, n-1); i++){
		temp = temp->next;
	}

	Vertice<VerticeInfo> * res = temp->value;

	PElement<Vertice<VerticeInfo>>::erasePointer(neighbors);

	return res;
}

template<>
Vertice<VerticeInfo> * FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::sight(
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo> * fantom) {

	PElement<Vertice<VerticeInfo>> * initialNeighbors = fantom->graph->neighbors(fantom->position);
	PElement<Vertice<VerticeInfo>> * temp = initialNeighbors;

	Vertice<VerticeInfo> * currentVertice;
	sf::Vector2<int> direction;
	sf::Vector2<int> diff;
	
	while(temp != NULL) {
		Vertice<VerticeInfo> * v = temp->value;
		currentVertice = v;

		direction = sf::Vector2<int>(
			currentVertice->value.info.pos.x - fantom->position->value.info.pos.x,
			currentVertice->value.info.pos.y - fantom->position->value.info.pos.y);

		while (currentVertice != NULL) {
			if (currentVertice->value.info.pacmanIsHere) {
				PElement<Vertice<VerticeInfo>>::erasePointer(initialNeighbors);
				return v;
			}
			else {
				PElement<Vertice<VerticeInfo>> * currentVerticeNeighbors = fantom->graph->neighbors(currentVertice);
				PElement<Vertice<VerticeInfo>> * temp2 = currentVerticeNeighbors;
				bool found = false;

				while(temp2 != NULL) {
					diff = sf::Vector2<int>(
						temp2->value->value.info.pos.x - currentVertice->value.info.pos.x,
						temp2->value->value.info.pos.y - currentVertice->value.info.pos.y);

					if (direction == diff) {
						found = true;
						currentVertice = temp2->value;
					}
					else {
						temp2 = temp2->next;
					}
				}
				if (!found)
					currentVertice = NULL;

				PElement<Vertice<VerticeInfo>>::erasePointer(currentVerticeNeighbors);
			}
		}
		temp = temp->next;
	}

	PElement<Vertice<VerticeInfo>>::erasePointer(initialNeighbors);

	return scent(fantom);
}

template<>
Vertice<VerticeInfo> * FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::scent(
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo> * fantom) {
	
	PElement<Edge<EdgeInfo, VerticeInfo>>* neighbors = fantom->graph->adjacentEdges(fantom->position);
	PElement<Edge<EdgeInfo, VerticeInfo>> * temp = neighbors;

	Vertice<VerticeInfo> * target = NULL;
	float highestHeatYet = 0.0f;

	while (temp != NULL) {
		if (temp->value->value.heat > highestHeatYet) {
			highestHeatYet = temp->value->value.heat;
			target = fantom->position == temp->value->begin ? temp->value->end : temp->value->begin;
		}
		temp = temp->next;
	}

	PElement<Edge<EdgeInfo, VerticeInfo>>::erasePointer(neighbors);

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