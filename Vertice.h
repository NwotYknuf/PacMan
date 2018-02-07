#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
#include <sstream>
#include <string>

#include "GElement.h"

using namespace std;

/**
 * Graph edge, has a degree and constains an information T
*/
template <class I>
class Vertice : public GElement<I>{
public:
int degree;	

Vertice(const int key, const I & v, bool Gom = false):GElement<I>(key,v),degree(0){}

operator string () const;

};

template <class I>
Vertice<I>::operator string () const{
ostringstream oss;

oss <<"Vertice("<<endl;
oss << "degree = " << degree << endl;
oss << GElement<I>::operator string();
oss<<")";
return oss.str();
}

template <class I>
ostream & operator << (ostream & os, const Vertice<I> & edge){
return os << (string)edge;
}

#endif