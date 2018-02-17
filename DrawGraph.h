#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include"EdgeInfo.h"
#include "VerticeInfo.h"

template<class P, class I>
class DrawGraph{
private :
	sf::Texture * _texture;
	Animator * _graphAnimator;
	sf::RenderWindow * _window;

public:
	DrawGraph(sf::RenderWindow * window, Animator * animator, sf::Texture * texture) :
		_window(window), _graphAnimator(animator), _texture(texture) { }

	bool draw(const Vertice<VerticeInfo> *_vertice);

	bool draw(const Edge<EdgeInfo, VerticeInfo> * s);
};

template<class P, class I>
bool DrawGraph<P,I>::draw(const Vertice<VerticeInfo> *vertice) {
	
	sf::Sprite sprite;
	sprite.setTexture(*_texture);
	
	sprite.setPosition(32 * vertice->value.info.pos.x, 32 * vertice->value.info.pos.y);

	_graphAnimator->setSprite(&sprite);

	if (vertice->value.info.pacGom) {
		_graphAnimator->setCurentAnimation("VerticePacgom");
	}
	else {
		_graphAnimator->setCurentAnimation("VerticeNoPacgom");
	}

	_graphAnimator->playAnimation();
	_window->draw(sprite);

	return true;
}

template<class P, class I>
bool DrawGraph<P, I>::draw(const Edge<EdgeInfo,VerticeInfo> * edge){
	
	sf::Sprite sprite;
	sprite.setTexture(*_texture);

	//position
	sf::Vector2<float> begin(edge->begin->value.info.pos.x, edge->begin->value.info.pos.y);
	sf::Vector2<float> diff(edge->end->value.info.pos.x - edge->begin->value.info.pos.x, edge->end->value.info.pos.y - edge->begin->value.info.pos.y);
	sf::Vector2<float> pos = begin + diff / 2.0f;
	sprite.setPosition((pos.x) * 32, (pos.y) * 32);

	//orientation

	string str = "Edge";
	switch (edge->value.direction) {
	case 1:
		str += "Horizontal";
		break;
	case 2:
		str += "TopRight";
		break;
	case 3:
		str += "Vertical";
		break;
	case 4:
		str += "TopLeft";
		break;
	default:
		break;
	}

	str += edge->value.pacGom ? "Pacgom" : "NoPacgom";

	_graphAnimator->setSprite(&sprite);
	_graphAnimator->setCurentAnimation(str);
	_graphAnimator->playAnimation();
	_window->draw(sprite);
	return true;
}

#endif // !DRAWGRAPH_H
