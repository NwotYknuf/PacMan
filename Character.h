#ifndef CHARACTER_H
#define CHARACTER_H

#include "Graph.h"
#include "PElement.h"
#include <utility>

template<class Info, class VerticeInformation>
class Character {
public:

	Info * info;
	Vertice<VerticeInformation> * position;

	Character(Info * _info, Vertice<VerticeInformation> * _pos) {
		info = _info;
		position = _pos;
	}

	template< class WINDOW>
	bool drawCharacter(WINDOW & window) const;

	template <class EdgeInformation>
	void move(Vertice<VerticeInformation>* vertice, Graph<EdgeInformation, VerticeInformation> * graph);

	template <class EdgeInformation>
	void move(const sf::Vector2<int> &vector, Graph<EdgeInformation, VerticeInformation> * graph);
};

template <class Info, class VerticeInformation>
template< class WINDOW>
bool Character<Info, VerticeInformation>::drawCharacter(WINDOW & window) const {

	if (!window.draw(this))
		return false;
	return true;

}

template<class Info, class VerticeInformation>
template<class EdgeInformation>
void Character<Info, VerticeInformation>::move(Vertice<VerticeInformation>* vertice, Graph<EdgeInformation, VerticeInformation>* graph) {
	PElement<Vertice<VerticeInformation>> * voisin;
	voisin = graph->neighbors(position);

	if (PElement < Vertice<VerticeInformation>>::inList(vertice, voisin)) {
		this->position = vertice;
	}
}

template<>
template<class EdgeInformation>
void Character<unsigned, sf::Vector2<int>>::move(
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
		
		sf::Vector2<int> diff(
			target->value.x - this->position->value.x,
			target->value.y - this->position->value.y);
			
		if (diff == vector) {
			this->position = target;
			return;
		}

		voisin = voisin->next;
	}
}

#endif 
