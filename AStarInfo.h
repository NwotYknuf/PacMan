#pragma once
#include "Vertice.h"
#include <iostream>

class AStarInfo{

public :
	static const int FREE = 1;
	static const int CLOSED = 2;
	static const int OPEN = 3;
	
	int state;
	float cost, heuristic, globalCost;
	AElement * father;

	explicit AStarInfo(AElement * father = NULL, const int state = FREE, const double & c = 0, const double & h = 0, const double & g = 0) :
		father(father), state(state), cost(c), heuristic(h), globalCost(g) { }

	friend ostream & operator << (ostream & os, const AStarInfo & info) { return os << (string)info; }

	operator string() const {
		ostringstream o; 
		o << "cost : " << state;
		o << "heuristic : " << cost;
		o << "globalCost : " << heuristic;
		o << "father : "<<  father;
		return o.str(); 
	}

};