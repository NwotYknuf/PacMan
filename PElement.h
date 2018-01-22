#pragma once
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

/**
 * template class for lists
**/

template<class T>
class PElement{
public:
	T* value;
	PElement<T>* next;

	PElement(T* _value, PElement<T>* _next) : value(_value), next(_next){ }

	static int size(const PElement<T> * l){
		return l->next == NULL ? 1: 1 + PElement<T>::size(l->next);
	}

	static const string toString(const PElement<T> * p,
		const char * begin = "( ",
		const char * separateur = ", ",
		const char * end = " )"){

		ostringstream stream;

		if (!p){
			stream << begin << end;
		}
		else{
			const PElement<T> *copy = p;
			stream << begin;

			while (copy->next){
				stream << *copy->value << separateur;
				copy = copy->next;
			}

			stream << *copy->value << end;
		}
		return stream.str();
	}

	static void insertOrdered(T * a, PElement<T> * & l,	bool(*lessOrEqual)(const T * a1, const T * a2)){

		if (!l){
			t = PElement<T>(a, NULL);
		}

		if(lessOrEqual(l->value, a)){
			l = new PElement(a, v);
		}
		else{
			insertOrdered(a, l->next, lessOrEqual);
		}
	}

	static T * unstack(PElement<T> * &l){
		if (!l){
			throw "bonjour";
		}

		T *val = l->value;
		PElement<T> *mem = l;
		l = l->next;
		delete(mem);

		return val;
	}

	static bool remove(const T * a, PElement<T> * & l){
		if (!l){
			return;
		}
				
		if (l->value == a){
			T *val = l->value;
			PElement<T> *mem = l;
			l = l->next;
			delete(mem);
			delete(val);
		}
		else{
			remove(a, l->next);
		}
	}

	static PElement<T> * copy(PElement<T> * l) {
		
		if (l->next != NULL) {
			return new PElement(new T(*l->value), copy(l->next));
		}
		else {
			return new PElement(new T(*l->value), NULL);
		}
	}

	static void erase(PElement<T>* & l) {
		if (l != NULL) {
			erase(l->next);
			delete(l->value);
			delete(l);
		}
		l = NULL;
	}

	static bool inList(const T * value, PElement<T> * l) {
		if (l == NULL) {
			return false;
		}
		else {
			return l->value == value || inList(value, l->next);
		}
	}

	template < class FONCTEUR>
	static PElement< T > * inList(PElement<T> * l, const FONCTEUR & condition) {
		if (l == NULL)
			return NULL;
		
		if (condition(l->value)) {
			return l;
		}
		else {
			return inList(l->next, condition);
		}
	}

};

