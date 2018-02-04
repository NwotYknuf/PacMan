#ifndef CHARACTER_H
#define CHARACTER_H

#include "Graph.h"
#include "PElement.h"
#include <utility>

template<class Info, class VerticeInformation>
class GCharacter {
public:

	Info * info;
	Vertice<VerticeInformation> * position;

	GCharacter(Info * _info, Vertice<VerticeInformation> * _pos) {
		info = _info;
		position = _pos;
	}

	template< class WINDOW>
	bool drawCharacter(WINDOW & window) const;

	template <class EdgeInformation>
	void move(Vertice<VerticeInformation>* vertice, Graph<EdgeInformation, VerticeInformation> * graph);
	
	template <class EdgeInformation>
	void move(const sf::Vector2<int> &vector, 
		Graph<EdgeInformation, VerticeInformation> * graph);

};

template <class Info, class VerticeInformation>
template< class WINDOW>
bool GCharacter<Info, VerticeInformation>::drawCharacter(WINDOW & window) const {

	if (!window.draw(this))
		return false;
	return true;

}

template<class Info, class VerticeInformation>
template<class EdgeInformation>
void GCharacter<Info, VerticeInformation>::move(
	Vertice<VerticeInformation>* vertice, 
	Graph<EdgeInformation, VerticeInformation>* graph) {
	
	PElement<Vertice<VerticeInformation>> * voisin;
	voisin = graph->neighbors(position);

	if (PElement < Vertice<VerticeInformation>>::inList(vertice, voisin)) {
		this->position = vertice;
	}
}

template<>
template<class EdgeInformation>
void GCharacter<unsigned, sf::Vector2<int>>::move(
	const sf::Vector2<int>& vector, 
	Graph<EdgeInformation, sf::Vector2<int>>* graph){

	PElement<Edge<EdgeInformation, sf::Vector2<int>>> * voisin;
	voisin = graph->adjacentEdges(position);

	while (voisin != NULL) {
		Vertice<sf::Vector2<int>> * target;
		
		if (this->position == voisin->value->begin) {
			target = voisin->value->end;
		}
		else {
			target = voisin->value->begin;
		}		
		
		sf::Vector2<int> diff(target->value - this->position->value);
			
		if (diff == vector) {
			this->position = target;
			return;
		}

		voisin = voisin->next;
	}
}

#endif 
