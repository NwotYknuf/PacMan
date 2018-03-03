#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include"EdgeInfo.h"
#include "VerticeInfo.h"
#include "Window.h"

template<class P, class I>
class DrawGraph : public Window{
private :
	sf::Texture * _texture;
	Animator * _graphAnimator;

public:
	DrawGraph(sf::RenderWindow * window, Animator * animator, 
		sf::Texture * texture, WorldToScreen worldToScreenTransform) 
		: Window(window, worldToScreenTransform), _graphAnimator(animator), _texture(texture) { }

	bool draw(const Vertice<VerticeInfo> *_vertice);

	bool draw(const Edge<EdgeInfo, VerticeInfo> * s);

	void update();
};

template<class P, class I>
bool DrawGraph<P,I>::draw(const Vertice<VerticeInfo> *vertice) {
	
	sf::Sprite sprite;
	sprite.setTexture(*_texture);
	
	sf::Vector2<float> screenCoord = _worldToScreenTransform(
		sf::Vector2<float>(vertice->value.info.pos.x,vertice->value.info.pos.y));

	sprite.setPosition(screenCoord.x, screenCoord.y);

	_graphAnimator->setSprite(&sprite);

	if (vertice->value.info.pacGom) {
		_graphAnimator->setCurentAnimation("VerticePacgom");
	}
	else {
		_graphAnimator->setCurentAnimation("VerticeNoPacgom");
	}

	_graphAnimator->playAnimation();

	//zoom
	sprite.setOrigin(sprite.getGlobalBounds().height / 2.0f, sprite.getGlobalBounds().width / 2.0f);
	float zoomX = _worldToScreenTransform.zoom / sprite.getGlobalBounds().width;
	float zoomY = _worldToScreenTransform.zoom / sprite.getGlobalBounds().height;
	sprite.setScale(sf::Vector2<float>(zoomX, zoomY));

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

	sf::Vector2<float> screenCoord = _worldToScreenTransform(pos);
	sprite.setPosition(screenCoord.x, screenCoord.y);

	
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

	//zoom
	sprite.setOrigin(sprite.getGlobalBounds().height / 2.0f, sprite.getGlobalBounds().width / 2.0f);
	float zoomX = _worldToScreenTransform.zoom / sprite.getGlobalBounds().width;
	float zoomY = _worldToScreenTransform.zoom / sprite.getGlobalBounds().height;
	sprite.setScale(sf::Vector2<float>(zoomX, zoomY));

	_window->draw(sprite);
	return true;
}

template<class P, class I>
void DrawGraph<P, I>::update() {
	_graphAnimator->update();
}

#endif // !DRAWGRAPH_H
