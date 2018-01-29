#pragma once
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

/**
 * template class for lists
**/

template<class I>
class PElement{
public:
	I* value;
	PElement<I>* next;

	PElement(I* _value, PElement<I>* _next) : value(_value), next(_next){ }

	static int size(const PElement<I> * l){
		return l->next == NULL ? 1: 1 + PElement<I>::size(l->next);
	}

	static const string toString(const PElement<I> * p,
		const char * begin = "( ",
		const char * separateur = ", ",
		const char * end = " )"){

		ostringstream stream;

		if (!p){
			stream << begin << end;
		}
		else{
			const PElement<I> *copy = p;
			stream << begin;

			while (copy->next){
				stream << *copy->value << separateur;
				copy = copy->next;
			}

			stream << *copy->value << end;
		}
		return stream.str();
	}

	static void insertOrdered(I * a, PElement<I> * & l,	bool(*lessOrEqual)(const I * a1, const I * a2)){

		if (!l){
			t = PElement<I>(a, NULL);
		}

		if(lessOrEqual(l->value, a)){
			l = new PElement(a, v);
		}
		else{
			insertOrdered(a, l->next, lessOrEqual);
		}
	}

	static I * unstack(PElement<I> * &l){
		if (!l){
			throw "bonjour";
		}

		I *val = l->value;
		PElement<I> *mem = l;
		l = l->next;
		delete(mem);

		return val;
	}

	static bool remove(const I * a, PElement<I> * & l){
		if (!l){
			return;
		}
				
		if (l->value == a){
			I *val = l->value;
			PElement<I> *mem = l;
			l = l->next;
			delete(mem);
			delete(val);
		}
		else{
			remove(a, l->next);
		}
	}

	static PElement<I> * copy(PElement<I> * l) {
		
		if (l->next != NULL) {
			return new PElement(new I(*l->value), copy(l->next));
		}
		else {
			return new PElement(new I(*l->value), NULL);
		}
	}

	static void erase(PElement<I>* & l) {
		if (l != NULL) {
			erase(l->next);
			delete(l->value);
			delete(l);
		}
		l = NULL;
	}

	static bool inList(const I * value, PElement<I> * l) {
		if (l == NULL) {
			return false;
		}
		else {
			return l->value == value || inList(value, l->next);
		}
	}

	template < class FONCTEUR>
	static PElement< I > * inList(PElement<I> * l, const FONCTEUR & condition) {
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

