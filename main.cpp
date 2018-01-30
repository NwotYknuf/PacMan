#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Error.h"
#include "Animation.h"
#include "Animator.h"
#include "Graph.h"
#include "Vertice.h"
#include "Edge.h"
#include "DrawGraph.h"
#include "GameClock.h"
#include "Character.h"
#include "DrawCharacter.h"

const float sqrt2 = 1.41421356237f;

using namespace std;

int main(){
	try {
	
		//initialisation
		sf::RenderWindow  window(sf::VideoMode(512, 512), "PacMan");
		sf::Event event;
		sf::View view1(sf::FloatRect(0, 0, 252, 252));//For now
		window.setView(view1);

#pragma region pacman
		sf::Texture texturePackman;
		if (!texturePackman.loadFromFile("sprites\\Packman.png")) {
			throw Error("Can't load Packman.png");
		}

		sf::Sprite pacmanSprite;
		pacmanSprite.setTexture(texturePackman);
		pacmanSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

		Animation walkLeft(&pacmanSprite, 0.166666667);
		walkLeft.addFrame(sf::IntRect(0, 0, 32, 32));
		walkLeft.addFrame(sf::IntRect(32, 0, 32, 32));

		Animation walkRight(&pacmanSprite, 0.166666667);
		walkRight.addFrame(sf::IntRect(0, 0, 32, 32));
		walkRight.addFrame(sf::IntRect(128, 0, 32, 32));

		Animation walkUp(&pacmanSprite, 0.166666667);
		walkUp.addFrame(sf::IntRect(0, 0, 32, 32));
		walkUp.addFrame(sf::IntRect(64, 0, 32, 32));

		Animation walkDown(&pacmanSprite, 0.166666667);
		walkDown.addFrame(sf::IntRect(0, 0, 32, 32));
		walkDown.addFrame(sf::IntRect(96, 0, 32, 32));

		Animator pacManAnimator;
		pacManAnimator.addAnimation("walkLeft", &walkLeft);
		pacManAnimator.addAnimation("walkRight", &walkRight);
		pacManAnimator.addAnimation("walkUp", &walkUp);
		pacManAnimator.addAnimation("walkDown", &walkDown);

#pragma endregion

#pragma region Graph

		Graph<EdgeInfo, sf::Vector2<int>> graph;

		Vertice<sf::Vector2<int>> * s0, *s1, *s2, *s3, *s4, *s5, *s6, *s7, *s8, *s9, *s10, *s11;
		s0 = graph.createVertice(sf::Vector2<int>(0, 0));
		s1 = graph.createVertice(sf::Vector2<int>(0, 1));
		s2 = graph.createVertice(sf::Vector2<int>(0, 2));
		s3 = graph.createVertice(sf::Vector2<int>(1, 0));
		s4 = graph.createVertice(sf::Vector2<int>(1, 1));
		s5 = graph.createVertice(sf::Vector2<int>(1, 2));
		s6 = graph.createVertice(sf::Vector2<int>(2, 0));
		s7 = graph.createVertice(sf::Vector2<int>(2, 1));
		s8 = graph.createVertice(sf::Vector2<int>(2, 2));
		s9 = graph.createVertice(sf::Vector2<int>(3, 3));
		s10 = graph.createVertice(sf::Vector2<int>(3, 4));
		s11 = graph.createVertice(sf::Vector2<int>(4,4));

		Edge<EdgeInfo, sf::Vector2<int>> *e0, *e1, *e2, *e3, *e4, *e5, *e6, *e7, *e8, *e9, *e10, *e11;
		EdgeInfo e;

		e.heat = 0;
		//1 East West
		e.direction = 1;
		e1 = graph.createEdge(e, s4, s1);
		e6 = graph.createEdge(e, s4, s7);
		e11 = graph.createEdge(e, s10, s11);

		// 2  North - East  South - West
		e.direction = 2;
		e2 = graph.createEdge(e, s4, s2);
		e5 = graph.createEdge(e, s4, s6);

		// 3 North South
		e.direction = 3;
		e3 = graph.createEdge(e, s4, s3);
		e4 = graph.createEdge(e, s4, s5);
		e9 = graph.createEdge(e, s9, s10);

		// 4 North - West South - East
		e.direction = 4;
		e0 = graph.createEdge(e, s4, s0);
		e7 = graph.createEdge(e, s4, s8);
		e8 = graph.createEdge(e, s8, s9);
		e10 = graph.createEdge(e, s9, s11);

		sf::Texture graphTexture;
		if (!graphTexture.loadFromFile("sprites\\tileset.png")) {
			throw Error("can't load tileset.png");
		}

		sf::Sprite prefabVertice;
		prefabVertice.setTexture(graphTexture);
		prefabVertice.setTextureRect(sf::IntRect(0, 0, 32, 32));

		sf::Sprite prefabEdge;
		prefabEdge.setTexture(graphTexture);
		prefabEdge.setTextureRect(sf::IntRect(32, 0, 32, 32));

		DrawGraph<float, sf::Vector2<int>> drawGraph(&window, &prefabVertice, &prefabEdge);
		
#pragma endregion
		
#pragma region fantom
		sf::Texture fantomTexture;

		if (!fantomTexture.loadFromFile("sprites\\fantom.png")) {
			throw Error("Can't load fantom.png");
		}

		sf::Sprite fantomSprite;
		fantomSprite.setTexture(fantomTexture);

		Animation fantomWalkLeft(&fantomSprite, 0.166666667);
		fantomWalkLeft.addFrame(sf::IntRect(0, 0, 32, 32));
		fantomWalkLeft.addFrame(sf::IntRect(32, 0, 32, 32));

		Animation fantomWalkRight(&fantomSprite, 0.166666667);
		fantomWalkRight.addFrame(sf::IntRect(64, 0, 32, 32));
		fantomWalkRight.addFrame(sf::IntRect(96, 0, 32, 32));

		Animation fantomWalkUp(&fantomSprite, 0.166666667);
		fantomWalkUp.addFrame(sf::IntRect(128, 0, 32, 32));
		fantomWalkUp.addFrame(sf::IntRect(160, 0, 32, 32));

		Animation fantomWalkDown(&fantomSprite, 0.166666667);
		fantomWalkDown.addFrame(sf::IntRect(192, 0, 32, 32));
		fantomWalkDown.addFrame(sf::IntRect(224, 0, 32, 32));

		Animation fantomWalkUpLeft(&fantomSprite, 0.166666667);
		fantomWalkUpLeft.addFrame(sf::IntRect(0, 32, 32, 32));
		fantomWalkUpLeft.addFrame(sf::IntRect(32, 32, 32, 32));

		Animation fantomWalkUpRight(&fantomSprite, 0.166666667);
		fantomWalkUpRight.addFrame(sf::IntRect(64, 32, 32, 32));
		fantomWalkUpRight.addFrame(sf::IntRect(96, 32, 32, 32));

		Animation fantomWalkDownRight(&fantomSprite, 0.166666667);
		fantomWalkDownRight.addFrame(sf::IntRect(128, 32, 32, 32));
		fantomWalkDownRight.addFrame(sf::IntRect(160, 32, 32, 32));

		Animation fantomWalkDownLeft(&fantomSprite, 0.166666667);
		fantomWalkDownLeft.addFrame(sf::IntRect(192, 32, 32, 32));
		fantomWalkDownLeft.addFrame(sf::IntRect(224, 32, 32, 32));

		Animation fantomStandStill(&fantomSprite, 0.333333333333);
		fantomStandStill.addFrame(sf::IntRect(0, 0, 32, 32));
		fantomStandStill.addFrame(sf::IntRect(64, 0, 32, 32));


		Animator fantomAnimator;
		fantomAnimator.addAnimation("walkLeft", &fantomWalkLeft);
		fantomAnimator.addAnimation("walkRight", &fantomWalkRight);
		fantomAnimator.addAnimation("walkUp", &fantomWalkUp);
		fantomAnimator.addAnimation("walkDown", &fantomWalkDown);
		fantomAnimator.addAnimation("walkDownLeft", &fantomWalkDownLeft);
		fantomAnimator.addAnimation("walkDownRight", &fantomWalkDownRight);
		fantomAnimator.addAnimation("walkUpLeft", &fantomWalkUpLeft);
		fantomAnimator.addAnimation("walkUpRight", &fantomWalkUpRight);
		fantomAnimator.addAnimation("standStill", &fantomStandStill);

		fantomAnimator.setCurentAnimation("walkLeft");

		Character<unsigned, Vertice<sf::Vector2<int>>> fantom(new unsigned(0), s0);

		DrawCharacter<unsigned, Vertice<sf::Vector2<int>>>  drawChar(&window, &fantomSprite);

#pragma endregion

		//main loop
		GameClock*clock = GameClock::getInstance();

		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {

					case sf::Keyboard::Numpad4:
						fantomAnimator.setCurentAnimation("walkLeft");
						fantom.move(s4, &graph);
						break;
					case sf::Keyboard::Numpad6:
						fantomAnimator.setCurentAnimation("walkRight");
						break;
					case sf::Keyboard::Numpad8:
						fantomAnimator.setCurentAnimation("walkUp");
						break;
					case sf::Keyboard::Numpad2:
						fantomAnimator.setCurentAnimation("walkDown");
						break;
					case sf::Keyboard::Numpad1:
						fantomAnimator.setCurentAnimation("walkDownLeft");
						break;
					case sf::Keyboard::Numpad3:
						fantomAnimator.setCurentAnimation("walkDownRight");
						break;
					case sf::Keyboard::Numpad7:
						fantomAnimator.setCurentAnimation("walkUpLeft");
						break;
					case sf::Keyboard::Numpad9:
						fantomAnimator.setCurentAnimation("walkUpRight");
						break;
					case sf::Keyboard::Numpad5:
						fantomAnimator.setCurentAnimation("standStill");
						break;						
					}
					break;
				default:
					break;
				}
			}

			if (clock->getElapsedTime() >= 1.0f/60.0f) {
				window.clear();
				graph.draw(drawGraph);
				window.draw(fantomSprite);
				fantomAnimator.playAnnimation();
				fantom.drawCharacter(drawChar);
				window.display();
				clock->restart();
			}
		}
	}
	catch (Error e) {
		cout << e << endl;
		system("pause");
		return -1;
	}

	return 0;
}
