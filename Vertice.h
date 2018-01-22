#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "GElement.h"

using namespace std;

/**
 * Graph edge, has a degree and constains an information T
*/
template <class T>
class Vertice : public GElement<T>{
public:
int degree;	

Vertice(const int key, const T & v):GElement<T>(key,v),degree(0){}

operator string () const;

};

template <class T>
Vertice<T>::operator string () const{
ostringstream oss;

oss <<"Vertice("<<endl;
oss << GElement<T>::operator string()<<endl;
oss<<"degree = " << degree << endl;
oss<<")";
return oss.str();
}

template <class T>
ostream & operator << (ostream & os, const Vertice<T> & edge){
return os << (string)edge;
}
