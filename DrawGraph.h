#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>

template<class S, class T>
class DrawGraph{
private :
	sf::Sprite * _vertice, *_edge;
	sf::RenderWindow * _window;
public:

	DrawGraph(sf::RenderWindow * window, sf::Sprite * vertice, sf::Sprite * edge) :
		_vertice(vertice), _edge(edge), _window(window){ }

	bool draw(const Vertice<T> *_vertice);

	bool draw(const Edge<S, T> * s);
};

template<class S, class T>
bool DrawGraph<S,T>::draw(const Vertice<T> *vertice) {
	int h = _vertice->getLocalBounds().height;
	int l = _vertice->getLocalBounds().width;

	sf::Sprite sprite;
	sprite.setTexture(*_vertice->getTexture());
	sprite.setTextureRect(_vertice->getTextureRect());

	sprite.setPosition(l * vertice->value.x, h * vertice->value.y);
	_window->draw(sprite);
	return true;
}

template<class S, class T>
bool DrawGraph<S, T>::draw(const Edge<S,T> * s){
	int height = _edge->getLocalBounds().height;
	int width = _edge->getLocalBounds().width;

	sf::Sprite sprite;
	sprite.setTexture(*_edge->getTexture());
	sprite.setTextureRect(_edge->getTextureRect());
	sprite.setOrigin(height / 2, width / 2);

	//position
	sf::Vector2<float> begin(s->begin->value.x, s->begin->value.y);
	sf::Vector2<float> diff(s->end->value.x - s->begin->value.x, s->end->value.y - s->begin->value.y);
	sf::Vector2<float> pos = begin + diff / 2.0f;
	sprite.setPosition((0.5f + pos.x )* height, (0.5f + pos.y) * width);
	
	//rotation
	float angle = 0.0f;

	if (diff.y == -1.0f) {
		if(diff.x == -1.0f)
			angle = -135.0f;
		if (diff.x == 0.0f)
			angle = -90.0f;
		if (diff.x == 1.0f)
			angle = 135.0f;
	}
	if (diff.y == 1.0f) {
		if (diff.x == -1.0f)
			angle = -45.0f;
		if (diff.x == 0.0f)
			angle = 90.0f;
		if (diff.x == 1.0f)
			angle = 45.0f;
	}

	sprite.setRotation(angle);

	_window->draw(sprite);
	return true;
}

#endif // !DRAWGRAPH_H
