#ifndef CHARACTER_H
#define CHARACTER_H

#include "Graph.h"
#include "PElement.h"
#include <utility>

template<class Info, class VerticeInfo>
class Character {
public:

	Info * info;
	Vertice<VerticeInfo> * position;

	Character(Info * _info, Vertice<VerticeInfo> * _pos) {
		info = _info;
		position = _pos;
	}

	template< class WINDOW>
	bool drawCharacter(WINDOW & window) const;

	template <class EdgeInformation>
	void move(Vertice<VerticeInfo>* vertice, Graph<EdgeInformation, VerticeInfo> * graph);

};

template <class Info, class VerticeInfo>
template< class WINDOW>
bool Character<Info, VerticeInfo>::drawCharacter(WINDOW & window) const {

	if (!window.draw(this))
		return false;
	return true;

}

template<class Info, class VerticeInfo>
template<class EdgeInformation>
void Character<Info, VerticeInfo>::move(Vertice<VerticeInfo>* vertice, Graph<EdgeInformation, VerticeInfo>* graph) {
	PElement<Vertice<VerticeInfo>> * voisin;
	voisin = graph->neighbors(position);

	if (PElement < Vertice<VerticeInfo>>::inList(vertice, voisin)) {
		this->position = vertice;
	}
}

#endif 
