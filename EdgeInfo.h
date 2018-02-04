#pragma once
#include<iostream>

using namespace std;

class EdgeInfo {

public:
	float heat;
	int direction;
	/*
	* 1 Horizontal
	* 2 Diagonal Right
	* 3 Vertical
	* 4 Diagonal Left
	*/

	EdgeInfo(float _heat, int _direction) 
		: heat(_heat), direction(_direction) { }
	
	EdgeInfo(const EdgeInfo &e) 
		: heat(e.heat), direction(e.direction) { }
	
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

		return os;
	}
	
};