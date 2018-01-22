#ifndef AELEMENT_H
#define AElEMENT_H
#include <iostream>
#include <string>
#include <sstream>
#include "AElement.h"

using namespace std;

template <class T>
class GElement : public AElement{
public:
	T value;
	GElement(const int key, const T & v) : AElement(key), value(v) { }

	operator string() const { ostringstream oss; oss << this->AElement::operator string() << ", value = " << value; return oss.str(); }

	friend ostream & operator << (ostream & os, const GElement<T>& gElement) { return os << (string)gElement; }
};

#endif