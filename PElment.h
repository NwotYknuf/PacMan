#pragma once
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

template<class T>
class PElement{
public:
	T* valeur;
	PElement<T>* suivant;

	PElement(T* Valeur, PElement<T>* Suivant) : valeur(Valeur), suivant(Suivant){ }

	static int taille(const PElement<T> * l){
		return l->suivant == NULL ? 1: 1 + PElement<T>::taille(l->suivant);
	}

	static const string toString(const PElement<T> * p,
		const char * debut = "( ",
		const char * separateur = ", ",
		const char * fin = " )"){

		ostringstream stream;

		if (!p){
			stream << debut << fin << endl;
		}
		else{
			const PElement<T> *copie = p;
			stream << debut;

			while (copie->suivant){
				stream << *copie->valeur << separateur;
				copie = copie->suivant;
			}

			stream << *copie->valeur << fin;
		}
		return stream.str();
	}

	static void insertionOrdonnee(T * a,
		PElement<T> * & l,
		bool(*estPlusPetitOuEgal)(const T * a1, const T * a2)){

		if (!l){
			t = PElement<T>(a, NULL);
		}

		if(estPlusPetitOuEgal(l->valeur)){
			l = new PElement(a, v);
		}
		else{
			insertionOrdonnee(a, l->suivant, estPlusPetitOuEgal);
		}
	}

	static T * depiler(PElement<T> * & l){
		if (!l){
			throw "bonjour";
		}

		T *val = l->valeur;
		PElement<T> *mem = l;
		l = l->suivant;
		delete(mem);

		return val;
	}

	static bool retire(const T * a, PElement<T> * & l){
		if (!l){
			return;
		}
				
		if (l->valeur == a){
			
		}
		else{
			retire(a, l->suivant);
		}


	}


};

