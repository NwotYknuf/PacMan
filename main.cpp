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
		sf::RenderWindow  window(sf::VideoMode(768, 768), "PacMan");
		sf::Event event;
		sf::View view1(sf::FloatRect(144, 144, 256, 256));//For now
		window.setView(view1);



#pragma region Graph

		Graph<EdgeInfo, sf::Vector2<int>> graph;
		vector<Vertice<sf::Vector2<int>>*> vertices;

		vertices.push_back(graph.createVertice(sf::Vector2<int>(5, 5)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(6, 5)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(7, 5)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(8, 5)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(9, 5)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(10, 5)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(11, 5)));
		
		vertices.push_back(graph.createVertice(sf::Vector2<int>(5, 6)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(6, 6)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(7, 6)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(8, 6)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(9, 6)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(10, 6)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(11, 6)));
		
		vertices.push_back(graph.createVertice(sf::Vector2<int>(5, 7)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(7, 7)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(8, 7)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(9, 7)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(11, 7)));

		vertices.push_back(graph.createVertice(sf::Vector2<int>(5, 8)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(6, 8)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(7, 8)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(8, 8)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(9, 8)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(10, 8)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(11, 8)));

		vertices.push_back(graph.createVertice(sf::Vector2<int>(5, 9)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(7, 9)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(8, 9)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(9, 9)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(11, 9)));
		
		vertices.push_back(graph.createVertice(sf::Vector2<int>(5, 10)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(6, 10)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(7, 10)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(8, 10)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(9, 10)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(10, 10)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(11, 10)));
		
		vertices.push_back(graph.createVertice(sf::Vector2<int>(5, 11)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(6, 11)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(7, 11)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(8, 11)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(9, 11)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(10, 11)));
		vertices.push_back(graph.createVertice(sf::Vector2<int>(11, 11)));


		vector<Edge<EdgeInfo, sf::Vector2<int>>*> edges;
		EdgeInfo e;

		e.heat = 0;
		//1 East West
		e.direction = 1;
		edges.push_back(graph.createEdge(e, vertices[0], vertices[1]));
		edges.push_back(graph.createEdge(e, vertices[1], vertices[2]));
		edges.push_back(graph.createEdge(e, vertices[2], vertices[3]));
		edges.push_back(graph.createEdge(e, vertices[3], vertices[4]));
		edges.push_back(graph.createEdge(e, vertices[4], vertices[5]));
		edges.push_back(graph.createEdge(e, vertices[5], vertices[6]));

		edges.push_back(graph.createEdge(e, vertices[8], vertices[9]));
		edges.push_back(graph.createEdge(e, vertices[9], vertices[10]));
		edges.push_back(graph.createEdge(e, vertices[10], vertices[11]));
		edges.push_back(graph.createEdge(e, vertices[11], vertices[12]));

		edges.push_back(graph.createEdge(e, vertices[19], vertices[20]));
		edges.push_back(graph.createEdge(e, vertices[20], vertices[21]));
		edges.push_back(graph.createEdge(e, vertices[21], vertices[22]));
		edges.push_back(graph.createEdge(e, vertices[22], vertices[23]));
		edges.push_back(graph.createEdge(e, vertices[23], vertices[24]));
		edges.push_back(graph.createEdge(e, vertices[24], vertices[25]));

		edges.push_back(graph.createEdge(e, vertices[32], vertices[33]));
		edges.push_back(graph.createEdge(e, vertices[33], vertices[34]));
		edges.push_back(graph.createEdge(e, vertices[34], vertices[35]));
		edges.push_back(graph.createEdge(e, vertices[35], vertices[36]));

		edges.push_back(graph.createEdge(e, vertices[38], vertices[39]));
		edges.push_back(graph.createEdge(e, vertices[39], vertices[40]));
		edges.push_back(graph.createEdge(e, vertices[40], vertices[41]));
		edges.push_back(graph.createEdge(e, vertices[41], vertices[42]));
		edges.push_back(graph.createEdge(e, vertices[42], vertices[43]));
		edges.push_back(graph.createEdge(e, vertices[43], vertices[44]));

		// 2  North - East  South - West
		e.direction = 2;

		edges.push_back(graph.createEdge(e, vertices[12], vertices[17]));
		edges.push_back(graph.createEdge(e, vertices[17], vertices[22]));
		edges.push_back(graph.createEdge(e, vertices[22], vertices[27]));
		edges.push_back(graph.createEdge(e, vertices[27], vertices[32]));
		
		// 3 North South
		e.direction = 3;

		edges.push_back(graph.createEdge(e, vertices[0], vertices[7]));
		edges.push_back(graph.createEdge(e, vertices[2], vertices[9]));
		edges.push_back(graph.createEdge(e, vertices[4], vertices[11]));
		edges.push_back(graph.createEdge(e, vertices[6], vertices[13]));

		edges.push_back(graph.createEdge(e, vertices[7], vertices[14]));
		edges.push_back(graph.createEdge(e, vertices[10], vertices[16]));
		edges.push_back(graph.createEdge(e, vertices[13], vertices[18]));

		edges.push_back(graph.createEdge(e, vertices[14], vertices[19]));
		edges.push_back(graph.createEdge(e, vertices[16], vertices[22]));
		edges.push_back(graph.createEdge(e, vertices[18], vertices[25]));

		edges.push_back(graph.createEdge(e, vertices[19], vertices[26]));
		edges.push_back(graph.createEdge(e, vertices[22], vertices[28]));
		edges.push_back(graph.createEdge(e, vertices[25], vertices[30]));

		edges.push_back(graph.createEdge(e, vertices[26], vertices[31]));
		edges.push_back(graph.createEdge(e, vertices[28], vertices[34]));
		edges.push_back(graph.createEdge(e, vertices[30], vertices[37]));

		edges.push_back(graph.createEdge(e, vertices[31], vertices[38]));
		edges.push_back(graph.createEdge(e, vertices[33], vertices[40]));
		edges.push_back(graph.createEdge(e, vertices[35], vertices[42]));
		edges.push_back(graph.createEdge(e, vertices[37], vertices[44]));

		// 4 North - West South - East
		e.direction = 4;

		edges.push_back(graph.createEdge(e, vertices[8], vertices[15]));
		edges.push_back(graph.createEdge(e, vertices[15], vertices[22]));
		edges.push_back(graph.createEdge(e, vertices[22], vertices[29]));
		edges.push_back(graph.createEdge(e, vertices[29], vertices[36]));


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

		pacManAnimator.setCurentAnimation("walkLeft");

		Character<unsigned, sf::Vector2<int>> pacman(new unsigned(0), vertices[44]);

		DrawCharacter<unsigned, sf::Vector2<int>>  drawCharPacman(&window, &pacmanSprite);

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

		Animation fantomStandStill(&fantomSprite, 0.45);
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

		fantomAnimator.setCurentAnimation("standStill");

		Character<unsigned, sf::Vector2<int>> fantom(new unsigned(0), vertices[0]);

		DrawCharacter<unsigned, sf::Vector2<int>>  drawCharFantom(&window, &fantomSprite);

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
						fantom.move<EdgeInfo>(sf::Vector2<int>(-1,0), &graph);
						break;
					case sf::Keyboard::Numpad6:
						fantomAnimator.setCurentAnimation("walkRight");
						fantom.move<EdgeInfo>(sf::Vector2<int>(1, 0), &graph);
						break;
					case sf::Keyboard::Numpad8:
						fantomAnimator.setCurentAnimation("walkUp");
						fantom.move<EdgeInfo>(sf::Vector2<int>(0, -1), &graph);
						break;
					case sf::Keyboard::Numpad2:
						fantomAnimator.setCurentAnimation("walkDown");
						fantom.move<EdgeInfo>(sf::Vector2<int>(0, 1), &graph);
						break;
					case sf::Keyboard::Numpad1:
						fantomAnimator.setCurentAnimation("walkDownLeft");
						fantom.move<EdgeInfo>(sf::Vector2<int>(-1, 1), &graph);
						break;
					case sf::Keyboard::Numpad3:
						fantomAnimator.setCurentAnimation("walkDownRight");
						fantom.move<EdgeInfo>(sf::Vector2<int>(1, 1), &graph);
						break;
					case sf::Keyboard::Numpad7:
						fantomAnimator.setCurentAnimation("walkUpLeft");
						fantom.move<EdgeInfo>(sf::Vector2<int>(-1, -1), &graph);
						break;
					case sf::Keyboard::Numpad9:
						fantomAnimator.setCurentAnimation("walkUpRight");
						fantom.move<EdgeInfo>(sf::Vector2<int>(1, -1), &graph);
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
				
				fantomAnimator.playAnnimation();
				window.draw(fantomSprite);
				fantom.drawCharacter(drawCharFantom);

				pacManAnimator.playAnnimation();
				window.draw(pacmanSprite);
				pacman.drawCharacter(drawCharPacman);

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
