#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>

template<class P, class I>
class DrawGraph{
private :
	sf::Sprite * _verticeSprite, *_edgeSprite;
	sf::RenderWindow * _window;
public:

	DrawGraph(sf::RenderWindow * window, sf::Sprite * vertice, sf::Sprite * edge) :
		_verticeSprite(vertice), _edgeSprite(edge), _window(window){ }

	bool draw(const Vertice<sf::Vector2<int>> *_vertice);

	bool draw(const Edge<EdgeInfo, sf::Vector2<int>> * s);
};

template<class P, class I>
bool DrawGraph<P,I>::draw(const Vertice<sf::Vector2<int>> *vertice) {
	int h = _verticeSprite->getLocalBounds().height;
	int l = _verticeSprite->getLocalBounds().width;

	sf::Sprite sprite;
	sprite.setTexture(*_verticeSprite->getTexture());
	sprite.setTextureRect(_verticeSprite->getTextureRect());

	sprite.setPosition(l * vertice->value.x, h * vertice->value.y);
	_window->draw(sprite);
	return true;
}

template<class P, class I>
bool DrawGraph<P, I>::draw(const Edge<EdgeInfo, sf::Vector2<int>> * edge){
	int height = _edgeSprite->getLocalBounds().height;
	int width = _edgeSprite->getLocalBounds().width;

	sf::Sprite sprite;
	sprite.setTexture(*_edgeSprite->getTexture());
	sprite.setTextureRect(_edgeSprite->getTextureRect());
	sprite.setOrigin(height / 2, width / 2);

	//position
	sf::Vector2<float> begin(edge->begin->value.x, edge->begin->value.y);
	sf::Vector2<float> diff(edge->end->value.x - edge->begin->value.x, edge->end->value.y - edge->begin->value.y);
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
