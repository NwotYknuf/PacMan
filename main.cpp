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

using namespace std;

int main()
{
	try {
	
		//initialisation
		sf::RenderWindow  window(sf::VideoMode(1280, 720), "PacMan");
		sf::Event event;

#pragma region pacmanInit
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
		pacManAnimator.addAnnimation("walkLeft", &walkLeft);
		pacManAnimator.addAnnimation("walkRight", &walkRight);
		pacManAnimator.addAnnimation("walkUp", &walkUp);
		pacManAnimator.addAnnimation("walkDown", &walkDown);

#pragma endregion

#pragma region phantomInit
		sf::Texture phantomTexture;

		if (!phantomTexture.loadFromFile("sprites\\fantom.png")) {
			throw Error("Can't load fantom.png");
		}

		sf::Sprite phantomSprite;
		phantomSprite.setTexture(phantomTexture);

		Animation lesDents(&phantomSprite, 0.166666667);
		lesDents.addFrame(sf::IntRect(0, 0, 32, 32));
		lesDents.addFrame(sf::IntRect(32, 0, 32, 32));

		Animator phantomAnimator;
		phantomAnimator.addAnnimation("lesDents", &lesDents);

		phantomAnimator.setCurentAnimation("lesDents");
#pragma endregion

#pragma region GraphInit

		Graph<float, sf::Vector2<int>> g;

		Vertice<sf::Vector2<int>> * s0, *s1, *s2, *s3, *s4, *s5, *s6, *s7, *s8, *s9, *s10, *s11;
		s0 = g.createVertice(sf::Vector2<int>(0, 0));
		s1 = g.createVertice(sf::Vector2<int>(0, 1));
		s2 = g.createVertice(sf::Vector2<int>(0, 2));
		s3 = g.createVertice(sf::Vector2<int>(1, 0));
		s4 = g.createVertice(sf::Vector2<int>(1, 1));
		s5 = g.createVertice(sf::Vector2<int>(1, 2));
		s6 = g.createVertice(sf::Vector2<int>(2, 0));
		s7 = g.createVertice(sf::Vector2<int>(2, 1));
		s8 = g.createVertice(sf::Vector2<int>(2, 2));
		s9 = g.createVertice(sf::Vector2<int>(3, 3));
		s10 = g.createVertice(sf::Vector2<int>(3, 4));
		s11 = g.createVertice(sf::Vector2<int>(4,4));

		Edge<float, sf::Vector2<int>> *e0, *e1, *e2, *e3, *e4, *e5, *e6, *e7, *e8, *e9, *e10, *e11;
		e0 = g.createEdge(0.0f, s4, s0);
		e1 = g.createEdge(0.0f, s4, s1);
		e2 = g.createEdge(0.0f, s4, s2);
		e3 = g.createEdge(0.0f, s4, s3);
		e4 = g.createEdge(0.0f, s4, s5);
		e5 = g.createEdge(0.0f, s4, s6);
		e6 = g.createEdge(0.0f, s4, s7);
		e7 = g.createEdge(0.0f, s4, s8);
		e8 = g.createEdge(0.0f, s8, s9);
		e9 = g.createEdge(0.0f, s9, s10);
		e10 = g.createEdge(0.0f, s9, s11);
		e11 = g.createEdge(0.0f, s10, s11);

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
		
		//main loop
		sf::Clock clock;
		float angle = 0;
		phantomSprite.setOrigin(32.0f, 32.0f);

		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {

					case sf::Keyboard::Q:
						pacManAnimator.setCurentAnimation("walkLeft");
						break;
					case sf::Keyboard::D:
						pacManAnimator.setCurentAnimation("walkRight");
						break;
					case sf::Keyboard::Z:
						pacManAnimator.setCurentAnimation("walkUp");
						break;
					case sf::Keyboard::S:
						pacManAnimator.setCurentAnimation("walkDown");
						break;
					}
					break;
				default:
					break;
				}
			}

			if (clock.getElapsedTime().asSeconds() >= 1.0f/60.0f) {				
				window.clear();
				g.draw(drawGraph);
				pacManAnimator.playAnnimation();
				window.draw(pacmanSprite);
				window.display();
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