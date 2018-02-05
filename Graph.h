#pragma once

#include <utility>
#include "PElement.h"
#include "Edge.h"
#include "Error.h"

template <class P, class I>
class Graph {
protected:

	int nextKey;

public:

	PElement< Vertice<I> > * lVertices;
	PElement< Edge<P, I> > * lEdges;

private:

	//doesn't update nextKey
	Vertice<I> * createVerticeNoIncrement(const int key, const I & info);

	void updateNextKey(const int key) { nextKey = max(1 + key, nextKey); }

	Vertice<I> * createVertice(const int key, const I & info) { updateNextKey(key); return createVerticeNoIncrement(key, info); }

public:

	Vertice<I> * createVertice(const I & info) { return createVerticeNoIncrement(nextKey++, info); }

private:
	//doesn't update nextKey
	Edge<P, I> * createEdgeNoIncrement(const int key, const P & info, Vertice<I> * begin, Vertice<I> * end);

	Edge<P, I> * createEdge(const int clef, const P & info, Vertice<I> * begin, Vertice<I> * end)
	{
		updateNextKey(clef);
		return createEdgeNoIncrement(clef, info, begin, end);
	}

public:

	Edge<P, I> * createEdge(const P & info, Vertice<I> * begin, Vertice<I> * end) { return createEdgeNoIncrement(nextKey++, info, begin, end); }

private:

	void copy(const Graph<P, I> & graph);

	void eraseAll();

public:

	Graph() : nextKey(0), lVertices(NULL), lEdges(NULL) {}

	Graph(const Graph<P, I> & graph) : Graph() { this->copy(graph); }

	const Graph<P, I> & operator = (const Graph<P, I> & graph) { this->eraseAll(); this->copy(graph); return *this; }

	~Graph() { this->eraseAll(); }

	int nbrVertices() const { return PElement< Vertice<I> >::size(lVertices); }

	int nbrEdges() const { return PElement< Edge<P, I> >::size(lEdges); }

	PElement< pair< Vertice<I> *, Edge<P, I>* > >  *  adjacent(const Vertice<I> * vertice) const;

	PElement< Edge<P, I> > *  adjacentEdges(const Vertice<I> * vertice) const;

	PElement< Vertice<I> > *  neighbors(const Vertice<I> * vertice) const;

	Edge<P, I> * getEdgesByVertices(const Vertice<I> * s1, const Vertice<I> * s2) const;

	operator string() const;

	template< class WINDOW>
	bool drawAllEdges(WINDOW & window) const;

	template< class WINDOW>
	bool drawAllVertices(WINDOW & window) const;

	template  <class WINDOW>
	bool draw(WINDOW & window) const;

};

template <class P, class I>
ostream & operator << (ostream & os, const Graph<P, I> & gr) { return os << (string)gr; }

template <class P, class I>
Vertice<I> * Graph<P, I>::createVerticeNoIncrement(const int key, const I & info) {
	Vertice<I> * createdVertice = new Vertice<I>(key, info);
	lVertices = new PElement< Vertice<I> >(createdVertice, lVertices);

	return createdVertice;
}

template <class P, class I>
Edge<P, I> * Graph<P, I>::createEdgeNoIncrement(const int key, const P & info, Vertice<I> * begin, Vertice<I> * end) {

	if (!PElement< Vertice<I> >::inList(begin, lVertices)) throw new Error("begin vertice undifined");
	if (!PElement< Vertice<I> >::inList(end, lVertices)) throw new Error( "begin vertice undifined");

	Edge<P, I> *  newVertice = new Edge<P, I>(key, info, begin, end);

	lEdges = new PElement< Edge<P, I> >(newVertice, lEdges);

	return newVertice;
}

template <class I>
class VerticeAlreadyInCopy {
public:
	const Vertice<I> * s;
	VerticeAlreadyInCopy(const Vertice<I> * s) :s(s) {}
	bool operator () (const Vertice<I> * vertice) const { return vertice->key == s->key; }
};

template <class P, class I>
void Graph<P, I>::copy(const Graph<P, I> & graph)
{
	const PElement<Vertice<I>> * pS;

	// Vertices first
	for (pS = graph.lVertices; pS; pS = pS->next) {
		const Vertice<I> * sommet = pS->value;
		this->createVertice(sommet->key, sommet->value);
	}

	//edges next

	const PElement<Edge<P, I>> * pA;
	for (pA = graph.lEdges; pA; pA = pA->next) {
		const Edge<P, I> * a = pA->value;
		Vertice<I> * d, *f;
		PElement< Vertice<I> > * p;
		VerticeAlreadyInCopy<I> conditionDebut(a->begin);
		p = PElement< Vertice<I> >::inList(lVertices, conditionDebut);
		d = p->value;

		VerticeAlreadyInCopy<I> conditionFin(a->end);
		p = PElement< Vertice<I> >::inList(lVertices, conditionFin);
		f = p->value;

		this->createVertice(a->key, a->value, d, f);
	}
}

template <class P, class I>
void Graph<P, I>::eraseAll() {
	PElement< Edge<P, I>>::eraseAll(this->lEdges);
	PElement<Vertice<I> >::eraseAll(this->lVertices);
	this->nextKey = 0;
}

template <class P, class I>
PElement< pair< Vertice<I> *, Edge<P, I>* > >  *  Graph<P, I>::adjacent(const Vertice<I> * vertice) const {
	const PElement< Edge<P, I> > * l;

	PElement< pair< Vertice<I> *, Edge<P, I>* > > * r;

	for (l = lEdges, r = NULL; l; l = l->next)

		if (vertice == l->value->begin)
			r = new PElement< pair< Vertice<I> *, Edge<P, I>* > >(new pair< Vertice<I> *, Edge<P, I>* >(l->value->end, l->value), r);
		else
			if (vertice == l->value->end)
				r = new PElement< pair< Vertice<I> *, Edge<P, I>* > >(new pair< Vertice<I> *, Edge<P, I>* >(l->value->begin, l->value), r);

	return r;
}


template <class P, class I>
PElement< Edge<P, I> > *  Graph<P, I>::adjacentEdges(const Vertice<I> * vertice) const {
	PElement< pair< Vertice<I> *, Edge<P, I>* > > * ladj = this->adjacent(vertice);
	PElement< pair< Vertice<I> *, Edge<P, I>* > > * l;

	PElement< Edge<P, I> > * r;

	for (l = ladj, r = NULL; l; l = l->next)
		r = new PElement< Edge<P, I> >(l->value->second, r);

	PElement< pair< Vertice<I> *, Edge<P, I>* > >::eraseAll(ladj);

	return r;
}

template <class P, class I>
PElement< Vertice<I> > *  Graph<P, I>::neighbors(const Vertice<I> * vertice) const
{
	PElement< pair< Vertice<I> *, Edge<P, I>* > > * ladj = this->adjacent(vertice);
	PElement< pair< Vertice<I> *, Edge<P, I>* > > * l;

	PElement< Vertice<I> > * r;

	for (l = ladj, r = NULL; l; l = l->next)
		r = new PElement< Vertice<I> >(l->value->first, r);

	PElement< pair< Vertice<I> *, Edge<P, I>* > >::eraseAll(ladj);

	return r;
}

template <class P, class I>
Edge<P, I> * Graph<P, I>::getEdgesByVertices(const Vertice<I> * s1, const Vertice<I> * s2) const
{
	PElement<Edge<P, I> > * l;

	for (l = this->lEdges; l; l = l->next)
		if (l->value->equals(s1, s2))
			return l->value;

	return NULL;
}


template <class P, class I>
Graph<P, I>::operator string() const
{
	ostringstream oss;
	oss << "Graphe( \n";
	oss << "prochaine clef = " << this->nextKey << endl;
	oss << "nombre de sommets = " << this->nbrVertices() << "\n";

	oss << PElement<Vertice<I> >::toString(lVertices, "", "\n", "\n");

	oss << "nombre d'arêtes = " << this->nbrEdges() << "\n";

	oss << PElement<Edge<P, I> >::toString(lEdges, "", "\n", "\n");
	oss << ")";
	return oss.str();
}

template <class P, class I>
template< class WINDOW>
bool Graph<P, I>::drawAllEdges(WINDOW & window) const{

	PElement< Edge<P, I>> * pA;
	for (pA = this->lEdges; pA; pA = pA->next)
		if (!window.draw(pA->value)) return false;

	return true;
}

template <class P, class I>
template< class WINDOW>
bool Graph<P, I>::drawAllVertices(WINDOW & window) const{
	PElement< Vertice<I>> * pS;
	for (pS = this->lVertices; pS; pS = pS->next)
		if (!window.draw(pS->value)) return false;
	return true;
}

template <class P, class I>
template< class WINDOW>
bool Graph<P, I>::draw(WINDOW & window) const{

	if (!this->drawAllEdges(window)) return false;

	return this->drawAllVertices(window);
}

template <class I, class WINDOW>
bool draw(const PElement<Vertice<I>> * path, WINDOW & window, const unsigned int color){
	if (!(path && path->next))
		return true;
	else	{

		window.draw(path->value, path->next->value, color);

		return draw(path->next, window, color);
	}
}

template<class I>
const I & max(const I &t1, const I &t2) {
	return t1 > t2 ? t1 : t2;
}