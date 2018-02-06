#ifndef GELEMENT_H
#define GELEMENT_H

#include <iostream>
#include <string>
#include <sstream>

#include "AElement.h"

using namespace std;

/**
 * Template for a graph element, contains a Key and a Value
*/

template <class I>
class GElement : public AElement{
public:
	I value;
	GElement(const int key, const I & v): AElement(key), value(v) { }

	operator string() const { 
		ostringstream o;
		o << this->AElement::operator string() << endl;
		o<< value;
		return o.str();
	}

	friend ostream & operator << (ostream & os, const GElement<I>& gElement) {
		return os << (string) gElement;
	}
};

#endif
