#pragma once
#include "AStarInfo.h"
#include "Informations.h"

class VerticeInfo{
public:
	Informations info;
	AStarInfo aStarInfo;

	VerticeInfo(const Informations &_info, const AStarInfo &_AStarInfo)
		: info(_info), aStarInfo(_AStarInfo) { }

	VerticeInfo(const Informations &_info)
		: info(_info), aStarInfo() { }

	operator string() const {
		ostringstream oss;
		oss << "Vertice informations : " << info << endl;
		oss << "A* informations : " << aStarInfo << endl;
		return oss.str();
	}

	friend ostream & operator <<(ostream & os, const VerticeInfo &v) { 
		return os << (string)v;
	}

};
