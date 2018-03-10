#pragma once

#include"WorldToScreen.h"

class Window {
public :
	sf::RenderWindow *_window;
	WorldToScreen _worldToScreenTransform;

	Window(sf::RenderWindow *window, WorldToScreen worldToScreenTransform) : _worldToScreenTransform(worldToScreenTransform){
		_window = window;
	}


};




