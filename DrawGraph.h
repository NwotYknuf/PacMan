#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include"EdgeInfo.h"
#include "VerticeInfo.h"

template<class P, class I>
class DrawGraph{
private :
	sf::Sprite * _verticeSprite, *_edgeSprite;
	sf::RenderWindow * _window;

public:
	DrawGraph(sf::RenderWindow * window, sf::Sprite * vertice, sf::Sprite * edge) :
		_verticeSprite(vertice), _edgeSprite(edge), _window(window){ }

	bool draw(const Vertice<VerticeInfo> *_vertice);

	bool draw(const Edge<EdgeInfo, VerticeInfo> * s);
};

template<class P, class I>
bool DrawGraph<P,I>::draw(const Vertice<VerticeInfo> *vertice) {
	int h = _verticeSprite->getLocalBounds().height;
	int l = _verticeSprite->getLocalBounds().width;

	sf::Sprite sprite;
	sprite.setTexture(*_verticeSprite->getTexture());
	sprite.setTextureRect(_verticeSprite->getTextureRect());

	sprite.setPosition(l * vertice->value.info.pos.x, h * vertice->value.info.pos.y);
	_window->draw(sprite);
	return true;
}

template<class P, class I>
bool DrawGraph<P, I>::draw(const Edge<EdgeInfo,VerticeInfo> * edge){
	int height = _edgeSprite->getLocalBounds().height;
	int width = _edgeSprite->getLocalBounds().width;

	sf::Sprite sprite;
	sprite.setTexture(*_edgeSprite->getTexture());
	sprite.setTextureRect(_edgeSprite->getTextureRect());
	sprite.setOrigin(height / 2, width / 2);

	//position
	sf::Vector2<float> begin(edge->begin->value.info.pos.x, edge->begin->value.info.pos.y);
	sf::Vector2<float> diff(edge->end->value.info.pos.x - edge->begin->value.info.pos.x, edge->end->value.info.pos.y - edge->begin->value.info.pos.y);
	sf::Vector2<float> pos = begin + diff / 2.0f;
	sprite.setPosition((0.5f + pos.x )* height, (0.5f + pos.y) * width);
	
	//"rotation"
	
	switch(edge->value.direction) {
	case 1:
		sprite.setTextureRect(sf::IntRect(32,0,32,32));
		break;
	case 2 :
		sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
		break;
	case 3 :
		sprite.setTextureRect(sf::IntRect(96, 0, 32, 32));
		break;
	case 4 :
		sprite.setTextureRect(sf::IntRect(128, 0, 32, 32));
		break;
	default:
		break;
	}

	_window->draw(sprite);
	return true;
}

#endif // !DRAWGRAPH_H
