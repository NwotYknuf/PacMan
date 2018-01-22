#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "AElement.h"

using namespace std;

/**
 * Template for a graph element, contains a Key and a Value
*/

template <class T>
class GElement : public AElement{
public:
T value;
GElement(const int key, const T & v): AElement(key), value(v) { }
operator string() const { ostringstream o; o << this->AElement::operator string() << ", value = " << value; return o.str();}

friend ostream & operator << (ostream & os, const GElement<T>& gElement) {return os << (string) gElement;}
};
