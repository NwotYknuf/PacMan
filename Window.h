#pragma once
#include <SFML\Graphics.hpp>
#include "WorldToScreen.h"
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

class Window {
public :
	sf::RenderWindow *_window;
	WorldToScreen _worldToScreenTransform;

	Window(sf::RenderWindow *window, WorldToScreen worldToScreenTransform) : _worldToScreenTransform(worldToScreenTransform){
		_window = window;
	}


};




