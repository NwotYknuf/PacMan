#ifndef AELEMENT_H
#define AELEMENT_H
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


class AElement
{
public:
	int key;

	explicit AElement(const int _key) : key(_key) {}
	operator string() const { ostringstream oss; oss << "key = " << key; return oss.str(); }

	friend ostream & operator << (ostream & os, const AElement& aElement) { return os << (string)aElement; }
};

#endif