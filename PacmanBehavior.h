#pragma once
#include <SFML\Graphics.hpp>
#include "GCharacter.h"
#include "Graph.h"

template <class Vinfo, class Einfo, class Cinfo>
class PacmanBehavior{
private:
	sf::Keyboard::Key _lastInput;
	sf::Vector2<int> v;
	float _timeElapsed = 0.0f;
	
	const static float UPDATE_RATE;

public:
	PacmanBehavior() { }
	~PacmanBehavior() { }

	void setLastInput(sf::Keyboard::Key input) { _lastInput = input; }
	void update(GCharacter<Vinfo, Einfo, Cinfo> * pacman);

};

template<class Vinfo, class Einfo, class Cinfo>
bool move(GCharacter<Vinfo, Einfo, Cinfo>* pacman, sf::Vector2<int> v) {

	PElement<Edge<EdgeInfo, VerticeInfo>> * voisin;
	voisin = pacman->graph->adjacentEdges(pacman->position);

	while (voisin != NULL) {

		Vertice<VerticeInfo> * target;

		if (pacman->position == voisin->value->begin)
			target = voisin->value->end;
		else
			target = voisin->value->begin;

		sf::Vector2<int> diff(target->value.info.pos - pacman->position->value.info.pos);

		if (diff == v) {
			pacman->updateInfos(target);
			return true;
		}

		voisin = voisin->next;
	}
	pacman->updateInfosFailure();
	return false;
}

template<class Vinfo, class Einfo, class Cinfo>
const float PacmanBehavior<Vinfo, Einfo, Cinfo>::UPDATE_RATE = 0.2f;

template<class Vinfo, class Einfo, class Cinfo>
void PacmanBehavior<Vinfo, Einfo, Cinfo>::update(GCharacter<Vinfo, Einfo, Cinfo>* pacman) {

	_timeElapsed += GameClock::getInstance()->getElapsedTime();

	if (_timeElapsed > UPDATE_RATE) {
		switch (_lastInput) {
		case sf::Keyboard::Numpad4:
			v = sf::Vector2<int>(-1, 0);
			break;
		case sf::Keyboard::Numpad6:
			v = sf::Vector2<int>(1, 0);
			break;
		case sf::Keyboard::Numpad8:
			v = sf::Vector2<int>(0, -1);
			break;
		case sf::Keyboard::Numpad2:
			v = sf::Vector2<int>(0, 1);
			break;
		case sf::Keyboard::Numpad1:
			v = sf::Vector2<int>(-1, 1);
			break;
		case sf::Keyboard::Numpad3:
			v = sf::Vector2<int>(1, 1);
			break;
		case sf::Keyboard::Numpad7:
			v = sf::Vector2<int>(-1, -1);
			break;
		case sf::Keyboard::Numpad9:
			v = sf::Vector2<int>(1, -1);
			break;
		case sf::Keyboard::Numpad5:
			v = sf::Vector2<int>(0, 0);
			break;
		}

		move(pacman, v);

		_timeElapsed -= UPDATE_RATE;
	}

}
