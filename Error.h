#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

class Error {
private :
	string _msg;

public:
	Error(string message);
	~Error();

	friend ostream& operator<<(ostream& os, const Error &erreur);
};

#endif // !ERROR_H
