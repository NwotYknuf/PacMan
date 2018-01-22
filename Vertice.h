#ifndef VERTICE_H
#define VERTICE_H
#include <iostream>
#include <sstream>
#include <string>
#include "GElement.h"

using namespace std;

template <class T>
class Vertice : public GElement<T>{
public:

	int degree;

	Vertice(const int key, const T & value) :GElement<T>(key, value), degree(0) { }

	operator string () const;

};

template <class T>
Vertice<T>::operator string () const{

	ostringstream oss;

	oss << "Vertice(" << endl;
	oss << GElement<T>::operator string() << endl;
	oss << "degree = " << degre << endl;
	oss << ")";
	return oss.str();
}

template <class T>
ostream & operator << (ostream & os, const Vertice<T> & sommet){
	return os << (string)sommet;
}

#endif