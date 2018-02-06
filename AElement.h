#ifndef AELEMENT_H
#define AELEMENT_H

#include <sstream>

using namespace std;

/**
Base element containing only a key
*/

class AElement{
public:
	int key;

	explicit AElement(const int _key): key(_key) { }

	operator string() const { 
		ostringstream o; 
		o <<"key = " << key ;
		return o.str();
	}

	friend ostream & operator << (ostream & os, const AElement& aElement) {
		return os << (string) aElement;
	}
};

#endif
