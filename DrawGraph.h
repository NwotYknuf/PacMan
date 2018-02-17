#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include"EdgeInfo.h"
#include "VerticeInfo.h"

template<class P, class I>
class DrawGraph{
private :
	sf::Sprite * _verticeSprite, *_edgeSprite, *_verticePacGomSprite, *_edgePacGomSprite;
	Animation * _pacGomEdge = NULL;
	Animator * _animEdge, *_animVertice;
	sf::RenderWindow * _window;

public:
	DrawGraph(sf::RenderWindow * window, sf::Sprite * vertice, sf::Sprite * edge, sf::Sprite * pacGomVertice, sf::Sprite * pacGomEdge, Animator * animEdge, Animator * animVertice) :
		_verticeSprite(vertice), _edgeSprite(edge), _window(window), _verticePacGomSprite(pacGomVertice), _edgePacGomSprite(pacGomEdge), _animEdge(animEdge), _animVertice(animVertice){}

	bool draw(const Vertice<VerticeInfo> *_vertice);

	bool draw(const Edge<EdgeInfo, VerticeInfo> * s);
};

template<class P, class I>
bool DrawGraph<P,I>::draw(const Vertice<VerticeInfo> *vertice) {
	float h = _verticeSprite->getLocalBounds().height;
	float l = _verticeSprite->getLocalBounds().width;

	sf::Sprite sprite;
	if (vertice->value.info.pacGom) {
		sprite.setTexture(*_verticePacGomSprite->getTexture());
		sprite.setTextureRect(_verticePacGomSprite->getTextureRect());
	} else {
		sprite.setTexture(*_verticeSprite->getTexture());
		sprite.setTextureRect(_verticeSprite->getTextureRect());
	}

	sprite.setPosition(l * vertice->value.info.pos.x, h * vertice->value.info.pos.y);
	if (vertice->value.info.pacGom)
		_animVertice->playAnimation();
	_window->draw(sprite);
	return true;
}

template<class P, class I>
bool DrawGraph<P, I>::draw(const Edge<EdgeInfo,VerticeInfo> * edge){
	float height = _edgeSprite->getLocalBounds().height;
	float width = _edgeSprite->getLocalBounds().width;

	sf::Sprite sprite;
	if (edge->value.pacGom) {
		sprite.setTexture(*_edgePacGomSprite->getTexture());
		sprite.setTextureRect(_edgePacGomSprite->getTextureRect());
	}
	else {
		sprite.setTexture(*_edgeSprite->getTexture());
		sprite.setTextureRect(_edgeSprite->getTextureRect());
	}
	sprite.setOrigin(height / 2, width / 2);

	//position
	sf::Vector2<float> begin(edge->begin->value.info.pos.x, edge->begin->value.info.pos.y);
	sf::Vector2<float> diff(edge->end->value.info.pos.x - edge->begin->value.info.pos.x, edge->end->value.info.pos.y - edge->begin->value.info.pos.y);
	sf::Vector2<float> pos = begin + diff / 2.0f;
	sprite.setPosition((0.5f + pos.x )* height, (0.5f + pos.y) * width);
	
	/*"rotation"
	* 1 Horizontal
	* 2 Diagonal Right
	* 3 Vertical
	* 4 Diagonal Left
	*/
	if (edge->value.pacGom) {

		switch (edge->value.direction) {
		case 1:
			_pacGomEdge.addAnimation(sf::IntRect(32, 32, 32, 32));
			_pacGomEdge.addAnimation(sf::IntRect(32, 64, 32, 32));
			break;
		case 2:
			_pacGomEdge.addAnimation(sf::IntRect(64, 32, 32, 32));
			_pacGomEdge.addAnimation(sf::IntRect(64, 64, 32, 32));
			break;
		case 3:
			_pacGomEdge.addAnimation(sf::IntRect(96, 32, 32, 32));
			_pacGomEdge.addAnimation(sf::IntRect(96, 64, 32, 32));
			break;
		case 4:
			_pacGomEdge.addAnimation(sf::IntRect(128, 32, 32, 32));
			_pacGomEdge.addAnimation(sf::IntRect(128, 64, 32,32));
			break;
		default:
			break;
		}
	}
	else {
		switch (edge->value.direction) {
		case 1:
			sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
			break;
		case 2:
			sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
			break;
		case 3:
			sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
			break;
		case 4:
			sprite.setTextureRect(sf::IntRect(128, 0, 32, 32));
			break;
		default:
			break;
		}
	}
	if (edge->value.pacGom)
		_animEdge->playAnimation();
	_window->draw(sprite);
	return true;
}

#endif // !DRAWGRAPH_H
