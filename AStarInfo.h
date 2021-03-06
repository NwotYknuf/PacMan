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

	explicit AStarInfo(AElement * father = NULL, const int state = FREE, const float & c = 0, const float & h = 0, const float & g = 0) :
		father(father), state(state), cost(c), heuristic(h), globalCost(g) { }

	friend ostream & operator << (ostream & os, const AStarInfo & info) { return os << (string)info; }

	operator string() const {
		ostringstream o; 
		o << "{ cost : " << state;
		o << " heuristic : " << cost;
		o << " globalCost : " << heuristic;
		o << " father : ";
		if (father != NULL)
			o << *father;
		else
			o<<"NULL";
		o << " }" << endl;
		return o.str(); 
	}

};