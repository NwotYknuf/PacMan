#ifndef CHARACTER_H
#define CHARACTER_H

#include "Graph.h"
#include "PElement.h"
#include <utility>

template<class I, class P>
class Character {
public:

	I info;
	P position;

	Character(I _info, P _pos) {
		info = _info;
		position = _pos;
	}

	template< class WINDOW>
	bool drawCharacter(WINDOW & window) const;

	void move(sf::Vector2<int> _displacement, Graph<float, sf::Vector2<int>> * graph);

};

template <class I, class P>
template< class WINDOW>
bool Character<I,P>::drawCharacter(WINDOW & window) const{

	if(!window.draw(this))
		return false;

	return true;

}

template<class I, class P>
inline void Character<I, P>::move(sf::Vector2<int> _displacement, Graph<float, sf::Vector2<int>>* graph){
	
	PElement< Edge<float, sf::Vector2<int>> > * adjacentEdges;
	adjacentEdges = graph->adjacentEdges();


}

#endif 
