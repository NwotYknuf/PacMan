#ifndef GCHARACTER_H
#define GCHARACTER_H

#include "Graph.h"
#include "PElement.h"
#include <utility>
#include "VerticeInfo.h"
#include "EdgeInfo.h"
#include "PacmanInfo.h"
#include "FantomInfo.h"

template<class Vinfo, class Einfo, class Cinfo>
class GCharacter {
private :
	Vertice<Vinfo> * _initialPosition;

public:
	Cinfo info;
	Vertice<Vinfo> * position;
	Graph<Einfo, Vinfo> * graph;

	GCharacter(Cinfo _info, Graph<Einfo, Vinfo>* _graph, Vertice<Vinfo> * initialPosition) {
		position = initialPosition;
		_initialPosition = initialPosition;
		info = _info;
		graph = _graph;
	}

	template< class WINDOW>
	bool drawCharacter(WINDOW & window) const;

	template< class BEHAVIOR>
	void update(BEHAVIOR & behavior);

	bool move(Vertice<Vinfo>* vertice);

	void updateInfos(Vertice<Vinfo>* vertice);

	void updateInfosFailure();

	void reset();
	
};

template <class Vinfo, class Einfo, class Cinfo>
template< class WINDOW>
bool GCharacter<Vinfo, Einfo, Cinfo>::drawCharacter(WINDOW & window) const {

	if (!window.draw(this))
		return false;
	return true;

}

template <class Vinfo, class Einfo, class Cinfo>
template< class BEHAVIOR>
void GCharacter<Vinfo, Einfo, Cinfo>::update(BEHAVIOR & behavior){
	behavior.update(this);
}

template<class Vinfo, class Einfo, class Cinfo>
bool GCharacter<Vinfo, Einfo, Cinfo>
::move(Vertice<Vinfo>* vertice) {

	PElement<Vertice<Vinfo>> * voisin;
	voisin = graph->neighbors(this->position);

	if (PElement < Vertice<Vinfo>>::inList(vertice, voisin)) {
		this->updateInfos(vertice);
		PElement < Vertice<Vinfo>>::erasePointer(voisin);
		return true;
	}
	else {
		this->updateInfosFailure();
		PElement < Vertice<Vinfo>>::erasePointer(voisin);
		return false;
	}
}

template<>
void GCharacter<VerticeInfo, EdgeInfo, FantomInfo>::updateInfos(Vertice<VerticeInfo>* vertice) {

	//Update direction vector
	this->info.direction = vertice->value.info.pos - this->position->value.info.pos;

	//change the position
	this->position = vertice;

}

template<>
void GCharacter<VerticeInfo, EdgeInfo, PacmanInfo>::updateInfos(Vertice<VerticeInfo>* vertice){

	//Update direction vector
	this->info.direction = vertice->value.info.pos - this->position->value.info.pos;

	//Update edge heat
	Edge<EdgeInfo, VerticeInfo> *v;
	v = graph->getEdgesByVertices(this->position, vertice);
	v->value.heat = 1.0f;

	//update packman is here
	this->position->value.info.pacmanIsHere = false;
	vertice->value.info.pacmanIsHere = true;

	//Update pacgoms
	if (v->value.pacGom) {
		v->value.pacGom = false;
		this->info.score++;
	}

	if (vertice->value.info.pacGom) {
		vertice->value.info.pacGom = false;
		this->info.score++;
	}

	//change the position
	this->position = vertice;

}

template<>
void GCharacter<VerticeInfo, EdgeInfo, PacmanInfo>::updateInfosFailure() {

	//Update direction vector
	this->info.direction = sf::Vector2<int>(0,0);

}

template<>
void GCharacter<VerticeInfo, EdgeInfo, FantomInfo>::updateInfosFailure() {

	//Update direction vector
	this->info.direction = sf::Vector2<int>(0, 0);

}

template<class Vinfo, class Einfo, class Cinfo>
void GCharacter<Vinfo, Einfo, Cinfo>::reset(){
	info.reset();
	position = _initialPosition;
}

#endif 
