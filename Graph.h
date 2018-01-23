#pragma once

#include <utility>
#include "PElement.h"
#include "Edge.h"
#include "Edge.h"

template <class S, class T>
class Graph {
protected:

	int nextKey;

public:

	PElement< Vertice<T> > * lVertices;
	PElement< Edge<S, T> > * lEdges;


private:

	//doesn't update nextKey
	Vertice<T> * createVerticeNoIncrement(const int key, const T & info);

	void updateNextKey(const int key) { nextKey = max(1 + key, nextKey); }

	Vertice<T> * createVertice(const int key, const T & info) { updateNextKey(key); return createVerticeNoIncrement(key, info); }

public:

	Vertice<T> * createVertice(const T & info) { return createVerticeNoIncrement(nextKey++, info); }

private:
	//doesn't update nextKey
	Edge<S, T> * createEdgeNoIncrement(const int key, const S & info, Vertice<T> * begin, Vertice<T> * end);

	Edge<S, T> * createEdge(const int clef, const S & info, Vertice<T> * begin, Vertice<T> * end)
	{
		updateNextKey(clef);
		return createEdgeNoIncrement(clef, info, begin, end);
	}

public:

	Edge<S, T> * createEdge(const S & info, Vertice<T> * begin, Vertice<T> * end) { return createEdgeNoIncrement(nextKey++, info, begin, end); }

private:

	void copy(const Graph<S, T> & graph);

	void eraseAll();

public:

	Graph() : nextKey(0), lVertices(NULL), lEdges(NULL) {}

	Graph(const Graph<S, T> & graph) : Graph() { this->copy(graph); }

	const Graph<S, T> & operator = (const Graph<S, T> & graph) { this->eraseAll(); this->copy(graph); return *this; }

	~Graph() { this->eraseAll(); }

	int nbrVertices() const { return PElement< Vertice<T> >::size(lVertices); }

	int nbrEdges() const { return PElement< Edge<S, T> >::size(lEdges); }

	PElement< pair< Vertice<T> *, Edge<S, T>* > >  *  adjacencent(const Vertice<T> * vertice) const;

	PElement< Edge<S, T> > *  adjacentVertices(const Vertice<T> * vertice) const;

	PElement< Vertice<T> > *  neighbors(const Vertice<T> * vertice) const;

	Edge<S, T> * getEdgesByVertices(const Vertice<T> * s1, const Vertice<T> * s2) const;

	operator string() const;

	template< class WINDOW>
	bool drawAllEdges(WINDOW & window) const;

	template< class WINDOW>
	bool drawAllVertices(WINDOW & window) const;

	template  <class WINDOW>
	bool draw(WINDOW & window) const;

};

template <class S, class T>
ostream & operator << (ostream & os, const Graph<S, T> & gr) { return os << (string)gr; }

template <class S, class T>
Vertice<T> * Graph<S, T>::createVerticeNoIncrement(const int key, const T & info) {
	Vertice<T> * createdVertice = new Vertice<T>(key, info);
	lVertices = new PElement< Vertice<T> >(createdVertice, lVertices);

	return createdVertice;
}

template <class S, class T>
Edge<S, T> * Graph<S, T>::createEdgeNoIncrement(const int key, const S & info, Vertice<T> * begin, Vertice<T> * end) {

	if (!PElement< Vertice<T> >::inList(begin, lVertices)) throw new Error("begin vertice undifined");
	if (!PElement< Vertice<T> >::inList(end, lVertices)) throw new Error( "begin vertice undifined");

	Edge<S, T> *  newVertice = new Edge<S, T>(key, info, begin, end);

	lEdges = new PElement< Edge<S, T> >(newVertice, lEdges);

	return newVertice;
}

template <class T>
class VerticeAlreadyInCopy {
public:
	const Vertice<T> * s;
	VerticeAlreadyInCopy(const Vertice<T> * s) :s(s) {}
	bool operator () (const Vertice<T> * vertice) const { return vertice->key == s->key; }
};

template <class S, class T>
void Graph<S, T>::copy(const Graph<S, T> & graph)
{
	const PElement<Vertice<T>> * pS;

	// Vertices first
	for (pS = graph.lVertices; pS; pS = pS->next) {
		const Vertice<T> * sommet = pS->value;
		this->createVertice(sommet->key, sommet->value);
	}

	//edges next

	const PElement<Edge<S, T>> * pA;
	for (pA = graph.lEdges; pA; pA = pA->next) {
		const Edge<S, T> * a = pA->value;
		Vertice<T> * d, *f;
		PElement< Vertice<T> > * p;
		VerticeAlreadyInCopy<T> conditionDebut(a->begin);
		p = PElement< Vertice<T> >::inList(lVertices, conditionDebut);
		d = p->value;

		VerticeAlreadyInCopy<T> conditionFin(a->end);
		p = PElement< Vertice<T> >::inList(lVertices, conditionFin);
		f = p->value;

		this->createVertice(a->key, a->value, d, f);
	}
}

template <class S, class T>
void Graph<S, T>::eraseAll() {
	PElement< Edge<S, T>>::erase(this->lEdges);
	PElement<Vertice<T> >::erase(this->lVertices);
	this->nextKey = 0;
}

template <class S, class T>
PElement< pair< Vertice<T> *, Edge<S, T>* > >  *  Graph<S, T>::adjacencent(const Vertice<T> * vertice) const {
	const PElement< Edge<S, T> > * l;

	PElement< pair< Vertice<T> *, Edge<S, T>* > > * r;

	for (l = lEdges, r = NULL; l; l = l->next)

		if (vertice == l->value->begin)
			r = new PElement< pair< Vertice<T> *, Edge<S, T>* > >(new pair< Vertice<T> *, Edge<S, T>* >(l->value->end, l->value), r);
		else
			if (vertice == l->value->end)
				r = new PElement< pair< Vertice<T> *, Edge<S, T>* > >(new pair< Vertice<T> *, Edge<S, T>* >(l->value->begin, l->value), r);

	return r;
}


template <class S, class T>
PElement< Edge<S, T> > *  Graph<S, T>::adjacentVertices(const Vertice<T> * vertice) const {
	PElement< pair< Vertice<T> *, Edge<S, T>* > > * ladj = this->adjacencent(vertice);
	PElement< pair< Vertice<T> *, Edge<S, T>* > > * l;

	PElement< Edge<S, T> > * r;

	for (l = ladj, r = NULL; l; l = l->next)
		r = new PElement< Edge<S, T> >(l->value->second, r);

	PElement< pair< Vertice<T> *, Edge<S, T>* > >::erase(ladj);

	return r;
}

template <class S, class T>
PElement< Vertice<T> > *  Graph<S, T>::neighbors(const Vertice<T> * vertice) const
{
	PElement< pair< Vertice<T> *, Edge<S, T>* > > * ladj = this->adjacencent(vertice);
	PElement< pair< Vertice<T> *, Edge<S, T>* > > * l;

	PElement< Vertice<T> > * r;

	for (l = ladj, r = NULL; l; l = l->next)
		r = new PElement< Vertice<T> >(l->value->first, r);

	PElement< pair< Vertice<T> *, Edge<S, T>* > >::erase(ladj);

	return r;
}

template <class S, class T>
Edge<S, T> * Graph<S, T>::getEdgesByVertices(const Vertice<T> * s1, const Vertice<T> * s2) const
{
	PElement<Edge<S, T> > * l;

	for (l = this->lEdges; l; l = l->next)
		if (l->value->equals(s1, s2))
			return l->value;

	return NULL;
}


template <class S, class T>
Graph<S, T>::operator string() const
{
	ostringstream oss;
	oss << "Graphe( \n";
	oss << "prochaine clef = " << this->nextKey << endl;
	oss << "nombre de sommets = " << this->nbrVertices() << "\n";

	oss << PElement<Vertice<T> >::toString(lVertices, "", "\n", "\n");

	oss << "nombre d'arêtes = " << this->nbrEdges() << "\n";

	oss << PElement<Edge<S, T> >::toString(lEdges, "", "\n", "\n");
	oss << ")";
	return oss.str();
}

template <class S, class T>
template< class WINDOW>
bool Graph<S, T>::drawAllEdges(WINDOW & window) const
{

	PElement< Edge<S, T>> * pA;
	for (pA = this->lEdges; pA; pA = pA->next)
		if (!window.draw(pA->value)) return false;

	return true;
}

template <class S, class T>
template< class WINDOW>
bool Graph<S, T>::drawAllVertices(WINDOW & window) const{
	PElement< Vertice<T>> * pS;
	for (pS = this->lVertices; pS; pS = pS->next)
		if (!window.draw(pS->value)) return false;
	return true;
}

template <class S, class T>
template< class WINDOW>
bool Graph<S, T>::draw(WINDOW & window) const{

	if (!this->drawAllEdges(window)) return false;

	return this->drawAllVertices(window);
}

template <class T, class WINDOW>
bool draw(const PElement<Vertice<T>> * path, WINDOW & window, const unsigned int color){
	if (!(path && path->next))
		return true;
	else	{

		window.draw(path->value, path->next->value, color);

		return draw(path->next, window, color);
	}
}

template<class T>
const T & max(const T &t1, const T &t2) {
	return t1 > t2 ? t1 : t2;
}