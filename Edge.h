#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "GElement.h"
#include "Vertice.h"

using namespace std;

/**
 * represents an edge with two Vertices and an information T
*/

template <class S, class T>
class Edge : public GElement<S>{
public:
Vertice <T> *begin, *end;

Edge( const int key, const S & v, Vertice<T> * _begin, Vertice<T> * _end) : GElement<S>( key, v) ,begin( _begin), end( _end){
_begin->degree++; _end->degree++;
}

~Edge() { begin->degree--; end->degree--; }

operator string () const;


/**
 * returns true if s1 == begin and s2 == end
 * */
bool equals( const Vertice<T> * s1, const Vertice<T> * s2) const;
};

template <class S, class T>
Edge<S,T>::operator string () const{
ostringstream oss;

oss <<"Edge  ("<< endl;
oss << GElement<S>::operator string()<<endl;
oss << "begin key = " << begin->key<< endl;
oss << "end key = " << end->key << endl;
oss << ")";
return oss.str();

}

template <class S, class T>
ostream & operator << (ostream & os, const Edge<S,T> & arete)
{
return os << (string)arete;
}

/**
 * returns true if s1 == begin and s2 == end
 * */
template <class S, class T>
bool Edge<S,T>::equals( const Vertice<T> * s1, const Vertice<T> * s2) const{
return (s1 == begin && s2 == end) || (s1 == end && s2 == begin);
}
