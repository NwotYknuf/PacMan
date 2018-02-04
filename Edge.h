#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <sstream>
#include <string>
#include "GElement.h"
#include "Vertice.h"

using namespace std;

/**
 * represents an edge with two Vertices and an information T
*/

template <class P, class I>
class Edge : public GElement<P>{
public:
Vertice <I> *begin, *end;

Edge( const int key, const P & v, Vertice<I> * _begin, Vertice<I> * _end) : GElement<P>( key, v) ,begin( _begin), end( _end){
_begin->degree++; _end->degree++;
}

~Edge() { begin->degree--; end->degree--; }

operator string () const;


/**
 * returns true if s1 == begin and s2 == end
 * */
bool equals( const Vertice<I> * s1, const Vertice<I> * s2) const;
};

template <class P, class I>
Edge<P,I>::operator string () const{
ostringstream oss;

oss <<"Edge  ("<< endl;
oss << GElement<P>::operator string()<<endl;
oss << "begin key = " << begin->key<< endl;
oss << "end key = " << end->key << endl;
oss << ")";
return oss.str();

}

template <class P, class I>
ostream & operator << (ostream & os, const Edge<P,I> & arete)
{
return os << (string)arete;
}

/**
 * returns true if s1 == begin and s2 == end
 * */
template <class P, class I>
bool Edge<P,I>::equals( const Vertice<I> * s1, const Vertice<I> * s2) const{
return (s1 == begin && s2 == end) || (s1 == end && s2 == begin);
}

#endif // !EDGE_H
