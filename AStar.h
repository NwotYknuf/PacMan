#pragma once
#include <utility>
#include"PElement.h"
#include "AStarTools.h"
#include "AStarInfo.h"

template <class G, class V>
class AStar {
public:

	static bool lessOrEqual(const V *v1, const V *v2) {
		return globalCost(v1) <= globalCost(v2);
	}

	static bool aStarTarget(G &graph, V *start, V*target,
		float(*computeHeuristic)(const V *v1, const V *v2)) {

		freeAllVertices(graph);
		PElement<V> * opened;
		father(start) = NULL; cost(start) = 0; 
		opened = new PElement<V>(start, NULL); state(start) = AStarInfo::OPEN;
		
		while (opened){

			V  * s = PElement<Vertice<VerticeInfo>>::unstack(opened); 
			state(s) = AStarInfo::CLOSED;

			if (s == target) { 
				PElement<V>::erasePointer(opened);
				return true;
			}

			PElement< pair<V*, float> > * neighbors = neighborsList(s, graph);
			PElement< pair<V*, float> > * l;

			for (l = neighbors; l; l = l->next){

				V * v = l->value->first;	
				float newCost = cost(s) + l->value->second;

				if (state(v) == AStarInfo::FREE){
					heuristic(v) = computeHeuristic(v, target);
					updateNeighbors(v, s, newCost, opened);
				}
				else {
					if (newCost < cost(v))
					{
						if (state(v) == AStarInfo::OPEN)
							PElement< V>::remove(v, opened);
							updateNeighbors(v, s, newCost, opened);
					}
				}
			}

			PElement< pair<V*, float> >::eraseAll(neighbors);
		}

		return false;

	}

	static V * aStar(G &graph, V *start, float(*computeHeuristic)(const V * s1)) {

		freeAllVertices(graph);
		PElement<V> * opened;

		father(start) = NULL;
		cost(start) = 0;

		opened = new PElement<V>(start, NULL); 
		state(start) = AStarInfo::OPEN;

		while (opened) {

			V  *s = PElement<V>::unstack(opened);
			state(s) = AStarInfo::CLOSED;
			
			if (isFinal(s)) {
				PElement<V>::erasePointer(opened);
				return s;
			}

			PElement< pair<V*, float> > * neighbors = neighborsList(s, graph);
			PElement< pair<V*, float> > * l;

			for (l = neighbors; l; l = l->next) {

				V *v = l->value->first;
				float newCost = cost(s) + l->value->second;

				if (state(v) == AStarInfo::FREE) {
					heuristic(v) = computeHeuristic(v);
					updateNeighbors(v, s, newCost, opened);
				}
				else
					if (newCost < cost(v)) {
						if (state(v) == AStarInfo::OPEN)
							PElement<V>::remove(v, opened);

						updateNeighbors(v, s, newCost, opened);
					}
			}
			PElement< pair<V*, float> >::eraseAll(neighbors);
		}

		return NULL;
	}

	static void updateNeighbors(V *v, V* s, const float & newCost, PElement<V> * &opened){
		father(v) = s;
		cost(v) = newCost;
		globalCost(v) = cost(v) + heuristic(v);
		PElement<V>::insertOrdered(v, opened, lessOrEqual); 
		state(v) = AStarInfo::FREE;
	}

};

template <class V>
PElement<V> * path(V *target, PElement<V> * & start){
	if (!target){
		start = NULL;
		return NULL;
	}
	else {
		if (!father(target)){
			start = new PElement<V>(target, NULL);
			return start;
		}
		else{
			PElement<V> * d = path(father(target), start);
			d->next = new PElement<V>(target, NULL);
			return d->next;
		}
	}
}
