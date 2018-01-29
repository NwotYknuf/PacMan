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

	bool draw(const Vertice<I> *_vertice);

	bool draw(const Edge<P, I> * s);
};

template<class P, class I>
bool DrawGraph<P,I>::draw(const Vertice<I> *vertice) {
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
bool DrawGraph<P, I>::draw(const Edge<P,I> * s){
	int height = _edgeSprite->getLocalBounds().height;
	int width = _edgeSprite->getLocalBounds().width;

	sf::Sprite sprite;
	sprite.setTexture(*_edgeSprite->getTexture());
	sprite.setTextureRect(_edgeSprite->getTextureRect());
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
