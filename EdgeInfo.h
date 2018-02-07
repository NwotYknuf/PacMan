#pragma once
#include<iostream>

using namespace std;

class EdgeInfo {

public:
	float heat;
	int direction;
	float distance;
	bool pacGom;
	/*
	* 1 Horizontal
	* 2 Diagonal Right
	* 3 Vertical
	* 4 Diagonal Left
	*/

	EdgeInfo(float _heat, int _direction, bool gom = false) 
		: heat(_heat), direction(_direction), pacGom(gom) { }
	
	EdgeInfo(const EdgeInfo &e, bool gom = false)
		: heat(e.heat), direction(e.direction), distance(e.distance), pacGom(gom) { }
	
	friend ostream& operator << (ostream& os, const EdgeInfo &e) {
		os << "heat : " << e.heat << " direction : ";

		switch (e.direction){
		case 1:
			os << "Horizontal";
			break;
		case 2:
			os << "Diagonal right";
			break;
		case 3:
			os << "Vertical";
			break;
		case 4:
			os << "Diagonal left";
		}

		os << "distance : " << e.distance;

		return os;
	}
	
};