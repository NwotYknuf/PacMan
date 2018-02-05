#pragma once

#include <utility>
#include"PElement.h"

/*
Explication de mes motivations qui ont conduit � cette solution pour A*.

L'algo A* doit �tre ind�pendant de :
1) la mani�re dont est repr�sent� un graphe
2) le th�me repr�sent� par le graphe (bref, du domaine d'application du graphe)
3) De la mani�re dont est repr�sent� un sommet

De plus, on veut que l'algo soit optimis� (en temps et en espace)

Il reste une op�ration qui peut �tre optimis�e : l'insertion en ordre sur la liste des ouverts : ici elle est O(n) alors qu'elle pourrait �tre faite en O(log n) en rempla�ant les
listes lin�aires par des arbres binaires � hauteur �quilibr�e


Notons dep, le sommet de d�part et cib, le sommet cible trouv�.
A*, pour fonctionner, a besoin pour tout sommet s des infos suivantes :
c : co�t r�el du chemin de dep � s
h : estimation (heuristique) du co�t du chemin de s � cib
g = c+h : estimation du co�t du chemin de dep � cib passant par s
pere : pointeur vers le sommet-p�re de s
etat : �tat du sommet : ferm�, ouvert ou libre
Je ne veux pas faire de ces infos des fonctions virtuelles : c'est trop co�teux et mal adapt� : les fonctions virtuelles conviennent bien pour les pbs o� les donn�es sont h�t�rog�nes
mais ce n'est pas le cas d'un graphe

*/

/**
suppose que pour tout s sommet de graphe, on a:
s.etat = LIBRE

suppose que les fonctions co�t et  h sont toujours >= 0
*/

template <class Graphe, class Sommet>
class AStarT
{
public:

	static bool estPlusPetitOuEgal(const Sommet * sommet1, const Sommet * sommet2)
	{
		return g(sommet1) <= g(sommet2);
	}
	
	/**

	recherche  dans graphe le plus court chemin de d�part � cible par l'algo A*.
	en cas de succ�s, les liens "p�re" des sommets indiquent le chemin � suivre en partant de cible vers d�part.
	le p�re de d�part vaut toujours NULL en sortie (c'est la racine du chemin ou bien encore la fin de la liste cha�n�e "p�re")

	retourne vrai si succ�s et faux si �chec

	suppose que tout sommet s du graphe
	dispose des attributs suivants publics :
	int etat (peut prendre l'une des 3 valeurs suivantes : LIBRE, OUVERT ou FERM�)
	pere : Sommet * pere
	double c;		// co�t r�el entre d�part et s
	double h;		// estimation du co�t entre s et cible
	double g;		// g == c+h

	suppose que la m�thode listeVoisins(sommet,graphe) retourne la liste des paires (voisin, co�t de l'ar�te sommet-voisin)

	hh est l'heuristique � appliquer entre 2 sommets quelconques du graphe

	*/
	static bool aStar1Cible(Graphe & graphe, Sommet * depart, Sommet * cible,
		double(*hh)(const Sommet * s1, const Sommet * s2)/*,
														 PElement< pair<Sommet*,double> > * (*listeVoisins)(const Sommet * s, const Graphe & graphe),
														 void (*libereToutSommet)(Graphe & graphe)*/)
	{
		libereToutSommet(graphe); // met tous les sommets du graphe � LIBRE et tous les liens-pere � NULL
		PElement<Sommet> * Ouverts;

		pere(depart) = NULL; c(depart) = 0; // depart->h = h(depart,cible); depart->g = depart->c + depart->h; // ces 2 derni�res affectations sont inutiles

		Ouverts = new PElement<Sommet>(depart, NULL); etat(depart) = OUVERT;

		while (Ouverts)
		{
			Sommet  * s = PElement<Sommet>::depiler(Ouverts); etat(s) = FERME;

			if (s == cible) { PElement<Sommet>::efface1(Ouverts); return true; }

			PElement< pair<Sommet*, double> > * listeDesVoisins = listeVoisins(s, graphe);
			PElement< pair<Sommet*, double> > * l;

			for (l = listeDesVoisins; l; l = l->s)		// on parcourt les voisins de s
			{
				Sommet * v = l->v->first;	// v est le voisin courant de s

				double nouveauCout = c(s) + l->v->second;			//l->v->second est le co�t de l'ar�te s - v

				if (etat(v) == LIBRE)
				{
					h(v) = hh(v, cible);
					miseAJourVoisin(v, s, nouveauCout, Ouverts);
				}
				else			// v est Ferm� ou Ouvert

					if (nouveauCout < c(v))
					{
						if (etat(v) == OUVERT)
							PElement< Sommet>::retire(v, Ouverts);

						miseAJourVoisin(v, s, nouveauCout, Ouverts);

					}				// if (nouveauCout < v->c)
			}			// for

			PElement< pair<Sommet*, double> >::efface2(listeDesVoisins);
		}	// while (Ouverts)

		return false; // �chec

	}	// aStar1Cible

		/**

		recherche  dans graphe le plus court chemin de d�part � un �tat final par l'algo A*.
		en cas de succ�s, les liens "p�re" des sommets indiquent le chemin � suivre en partant du sommet-cible trouv� vers d�part.
		le p�re de d�part vaut toujours NULL en sortie (c'est la racine du chemin ou bien encore la fin de la liste cha�n�e "p�re")

		retourne un pointeur sur le sommet-cible trouv�  (le 1er sommet rencontr� qui satisfait estFinal()) si succ�s et NULL si �chec

		suppose que tout sommet s du graphe
		dispose des attributs suivants publics :
		int etat (peut prendre l'une des 3 valeurs suivantes : LIBRE, OUVERT ou FERM�)
		pere : Sommet * pere
		double c;		// co�t r�el entre d�part et s
		double h;		// estimation du co�t entre s et cible
		double g;		// g == c+h

		suppose que la m�thode listeVoisins(sommet,graphe) retourne la liste des paires (voisin, co�t de l'ar�te sommet-voisin)

		hh est l'heuristique � appliquer entre 1 sommet quelconque du graphe et un �tat final

		bool estFinal(const Sommet * s) est une m�thode indiquant si le sommet correspond � un �tat final

		*/
	static Sommet * aStar(Graphe & graphe, Sommet * depart,
		double(*hh)(const Sommet * s)/*,
									 PElement< pair<Sommet*,double> > * (*listeVoisins)(const Sommet * s, const Graphe & graphe),
									 void (*libereToutSommet)(Graphe & graphe)*/)
	{
		libereToutSommet(graphe); // met tous les sommets du graphe � LIBRE et tous les liens-pere � NULL
		PElement<Sommet> * Ouverts;

		pere(depart) = NULL; c(depart) = 0; // depart->h = h(depart,cible); depart->g = depart->c + depart->h; // ces 2 derni�res affectations sont inutiles

		Ouverts = new PElement<Sommet>(depart, NULL); etat(depart) = OUVERT;

		while (Ouverts)
		{
			Sommet  * s = PElement<Sommet>::depiler(Ouverts); etat(s) = FERME;

			if (estFinal(s)) { PElement<Sommet>::efface1(Ouverts); return s; }

			PElement< pair<Sommet*, double> > * listeDesVoisins = listeVoisins(s, graphe);
			PElement< pair<Sommet*, double> > * l;

			for (l = listeDesVoisins; l; l = l->s)		// on parcourt les voisins de s
			{
				Sommet * v = l->v->first;	// v est le voisin courant de s

				double nouveauCout = c(s) + l->v->second;			//l->v->second est le co�t de l'ar�te s - v

				if (etat(v) == LIBRE)
				{
					h(v) = hh(v);
					miseAJourVoisin(v, s, nouveauCout, Ouverts);
				}
				else			// v est Ferm� ou Ouvert

					if (nouveauCout < c(v))
					{
						if (etat(v) == OUVERT)
							PElement< Sommet>::retire(v, Ouverts);

						miseAJourVoisin(v, s, nouveauCout, Ouverts);

					}				// if (nouveauCout < v->c)
			}			// for

			PElement< pair<Sommet*, double> >::efface2(listeDesVoisins);
		}	// while (Ouverts)

		return NULL; // �chec

	}	// aStar



	static void miseAJourVoisin(Sommet * v, Sommet * s, const double & nouveauCout, PElement<Sommet> * & Ouverts)
	{
		pere(v) = s;
		c(v) = nouveauCout;
		g(v) = c(v) + h(v);
		PElement<Sommet>::insertionOrdonnee(v, Ouverts, estPlusPetitOuEgal); etat(v) = OUVERT;
	}




}; // AStarT

   /**
   T�che : Construit sous une forme plus pratique le r�sultat de l'algo A* :
   transforme sous forme de liste cha�n�e PElement<Sommet> la liste cha�n�e d�finie par les liens p�re qui a �t� produite par A*.

   Rappel : L'algo A* cr�e une liste cha�n�e dont le maillon de t�te est cible et dont le maillon final est d�part.
   La m�thode chemin(,) construit une liste cha�n�e qui inverse le sens de parcours de la liste "lien p�re" produite par A*.
   DONNEES :
   cible : sommet final trouv� par A* (celui qui v�rifie la condition estFinal(...))

   RESULTATS : debut : qui pointe sur le 1er maillon de la nouvelle liste cr��e (il pointe donc aussi sur le sommet depart de l'algo A*)
   et par return un pointeur sur le dernier maillon de la liste cha�n�e PElement<Sommet> * construite.
   Le pointeur renvoy� par return pointe donc sur cible.

   HYPOTHESE :
   */
template <class Sommet>
PElement<Sommet> * path(Sommet * cible, PElement<Sommet> * & debut)
{
	if (!cible) 	// le chemin trouv� est vide (il n'y a donc pas de chemin)
	{
		debut = NULL; return NULL;
	}

	else
		if (!pere(cible))		// le chemin trouv� contient un seul sommet. Cela signifie que d�part = cible
		{
			debut = new PElement<Sommet>(cible, NULL);
			return debut;
		}
		else	// le chemin trouv� a au moins 2 sommets
		{
			PElement<Sommet> * d = path(pere(cible), debut);
			d->s = new PElement<Sommet>(cible, NULL);
			return d->s;
		}
}



