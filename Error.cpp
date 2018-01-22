#include "Error.h"

Error::Error(string msg) : _msg(msg){ }

Error::~Error(){ }

ostream & operator<<(ostream & os, const Error & erreur){
	os << erreur._msg;
	return os;
}
