#pragma once

/**
Motivations qui ont conduit à cette solution pour représenter un graphe :

hypothèses : Un graphe est non orienté. Dans le cas général, une information est associée à chaque sommet, à chaque arête : un nom, un n°, une couleur, etc.

J'ignore totalement la nature de cette information, d'où template <S,T>.
S : info associée à une arête
T : info associée à un sommet

chaque élément du graphe est identifié par une clef unique. Celle-ci est générée automatiquement par l'attribut prochaineClef du graphe.
Celle-ci définit à tout instant la clef qui sera attribuée au prochain élément créé dans le graphe.

*/

#include <utility>
#include "PElement.h"
#include "Edge.h"
#include "Edge.h"

/*
classe sachant dessiner un graphe

	template <class S, class T> class Dessinateur;
*/

template <class S, class T>
class Graphe {
protected:

	/** la  clef qui sera attribuée au prochain élément (sommet ou arête) créé dans le graphe par les méthodes creeSommet(info)
	ou creeArete(info,debut,fin) fonctionne comme auto-increment d'une base de données */

	int nextKey;

public:

	PElement< Vertice<T> > * lVertices; // liste de sommets
	PElement< Edge<S, T> > * lEdges; // liste d'arêtes

	//------------------- opérations de création ----------------------------------------------

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

	Edge<S, T> * createVertice(const int clef, const S & info, Vertice<T> * begin, Vertice<T> * end)
	{
		updateNextKey(clef);
		return createEdgeNoIncrement(clef, info, begin, end);
	}

public:
	/**
	 * crée une arête joignant les 2 sommets debut et fin
	 *
	 * met à jour les champs degre de debut et de fin
	 *
	 * met à jour prochaineClef
	 *
	 * */

	Edge<S, T> * createVertice(const S & info, Vertice<T> * begin, Vertice<T> * end) { return createEdgeNoIncrement(nextKey++, info, begin, end); }

private:

	void copy(const Graphe<S, T> & graph);

	void eraseAll();

public:

	Graphe() : nextKey(0), lVertices(NULL), lEdges(NULL) {}

	Graphe(const Graphe<S, T> & graph) : Graphe() { this->copy(graph); }

	const Graphe<S, T> & operator = (const Graphe<S, T> & graph) { this->eraseAll(); this->copy(graph); return *this; }

	~Graphe() { this->eraseAll(); }

	int nbrVertices() const { return PElement< Vertice<T> >::size(lVertices); }

	int nbrEdges() const { return PElement< Edge<S, T> >::size(lEdges); }


	/**
	 * returns the list of (vertice/edges) adjacent to the Vertice
	*/
	PElement< pair< Vertice<T> *, Edge<S, T>* > >  *  adjacences(const Vertice<T> * vertice) const;

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
ostream & operator << (ostream & os, const Graphe<S, T> & gr) { return os << (string)gr; }

template <class S, class T>
Vertice<T> * Graphe<S, T>::createVerticeNoIncrement(const int key, const T & info) {
	Vertice<T> * createdVertice = new Vertice<T>(key, info);
	lVertices = new PElement< Vertice<T> >(createdVertice, lVertices);

	return createdVertice;
}

template <class S, class T>
Edge<S, T> * Graphe<S, T>::createEdgeNoIncrement(const int key, const S & info, Vertice<T> * begin, Vertice<T> * end) {

	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (!PElement< Vertice<T> >::inList(begin, lVertices)) throw "début d'arête non défini";
	if (!PElement< Vertice<T> >::inList(end, lVertices)) throw "fin d'arête non définie";

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
void Graphe<S, T>::copy(const Graphe<S, T> & graph)
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
void Graphe<S, T>::eraseAll() {
	PElement< Edge<S, T>>::erase(this->lEdges);
	PElement<Vertice<T> >::erase(this->lVertices);
	this->nextKey = 0;
}

template <class S, class T>
PElement< pair< Vertice<T> *, Edge<S, T>* > >  *  Graphe<S, T>::adjacences(const Vertice<T> * vertice) const {
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
PElement< Edge<S, T> > *  Graphe<S, T>::adjacentVertices(const Vertice<T> * vertice) const {
	PElement< pair< Vertice<T> *, Edge<S, T>* > > * ladj = this->adjacences(vertice);
	PElement< pair< Vertice<T> *, Edge<S, T>* > > * l;

	PElement< Edge<S, T> > * r;

	for (l = ladj, r = NULL; l; l = l->next)
		r = new PElement< Edge<S, T> >(l->value->second, r);

	PElement< pair< Vertice<T> *, Edge<S, T>* > >::erase(ladj);

	return r;
}

template <class S, class T>
PElement< Vertice<T> > *  Graphe<S, T>::neighbors(const Vertice<T> * vertice) const
{
	PElement< pair< Vertice<T> *, Edge<S, T>* > > * ladj = this->adjacences(vertice);
	PElement< pair< Vertice<T> *, Edge<S, T>* > > * l;

	PElement< Vertice<T> > * r;

	for (l = ladj, r = NULL; l; l = l->next)
		r = new PElement< Vertice<T> >(l->value->first, r);

	PElement< pair< Vertice<T> *, Edge<S, T>* > >::erase(ladj);

	return r;
}

template <class S, class T>
Edge<S, T> * Graphe<S, T>::getEdgesByVertices(const Vertice<T> * s1, const Vertice<T> * s2) const
{
	PElement<Edge<S, T> > * l;

	for (l = this->lEdges; l; l = l->next)
		if (l->value->equals(s1, s2))
			return l->value;

	return NULL;
}


template <class S, class T>
Graphe<S, T>::operator string() const
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
bool Graphe<S, T>::drawAllEdges(WINDOW & window) const
{

	PElement< Edge<S, T>> * pA;
	for (pA = this->lEdges; pA; pA = pA->next)
		if (!window.dessine(pA->value)) return false;

	return true;
}

template <class S, class T>
template< class WINDOW>
bool Graphe<S, T>::drawAllVertices(WINDOW & window) const{
	PElement< Vertice<T>> * pS;
	for (pS = this->lVertices; pS; pS = pS->next)
		if (!window.dessine(pS->value)) return false;
	return true;
}

template <class S, class T>
template< class WINDOW>
bool Graphe<S, T>::draw(WINDOW & window) const
{

	if (!this->drawAllEdges(window)) return false;

	return this->drawAllVertices(window);
}

template <class T, class WINDOW>
bool dessine(const PElement<Vertice<T>> * path, WINDOW & window, const unsigned int color)
{
	if (!(path && path->next))
		return true;

	else		// le chemin contient au moins une arête
	{
		// on dessine d'abord la 1ère arête

		window.dessine(path->value, path->next->value, color);

		return dessine(path->next, window, color);		// puis on dessine les arêtes suivantes
	}
}

template<class T>
const T & max(const T &t1, const T &t2) {
	return t1 > t2 ? t1 : t2;
}