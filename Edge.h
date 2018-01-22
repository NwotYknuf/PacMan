#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <sstream>
#include <string>
#include "GElement.h"
#include "Vertice.h"

using namespace std;

template <class S, class T>
class Edge : public GElement<S>{
public:
	Sommet <T> *start, *end;	

	Edge(const int clef, const S & v, Sommet<T> * debut, Sommet<T> * fin) : GElement<S>(clef, v), start(debut), end(fin){
		debut->degre++; fin->degre++;
	}

	~Edge() { start->degre--; end->degre--; }

	operator string () const;

	bool estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const;
};

template <class S, class T>
Edge<S, T>::operator string () const{

	ostringstream oss;

	oss << "Edge  (" << endl;
	oss << GElement<S>::operator string() << endl;
	oss << "begin key = " << start->clef << endl;
	oss << "end key = " << end->clef << endl;
	oss << ")";
	return oss.str();

}

template <class S, class T>
ostream & operator << (ostream & os, const Edge<S, T> & arete){

	return os << (string)arete;
}

template <class S, class T>
bool Edge<S, T>::estEgal(const Sommet<T> * s1, const Sommet<T> * s2) const{

	return (s1 == start && s2 == end) || (s1 == end && s2 == start);
}

#endif // !EDGE_H