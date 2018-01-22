#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include"Error.h"
#include "Animation.h"
#include "Animator.h"

using namespace std;

int main()
{
	try {
		//initialisation
		sf::RenderWindow  window(sf::VideoMode(1280, 720), "My window");
		sf::Event event;

		sf::Texture texturePackman;
		if (!texturePackman.loadFromFile("sprites\\Packman.png")) {
			throw Error("Can't load Packman.png");
		}
		
		sf::Sprite pacmanSprite;
		pacmanSprite.setTexture(texturePackman);

		Animation walkLeft(&pacmanSprite, 0.166666667);
		walkLeft.addFrame(sf::IntRect(0, 0, 32, 32));
		walkLeft.addFrame(sf::IntRect(32, 0, 32, 32));

		Animation walkRight(&pacmanSprite, 0.166666667);
		walkRight.addFrame(sf::IntRect(64, 0, 32, 32));
		walkRight.addFrame(sf::IntRect(96, 0, 32, 32));

		Animation walkUp(&pacmanSprite, 0.166666667);
		walkUp.addFrame(sf::IntRect(128, 0, 32, 32));
		walkUp.addFrame(sf::IntRect(160, 0, 32, 32));

		Animation walkDown(&pacmanSprite, 0.166666667);
		walkDown.addFrame(sf::IntRect(192, 0, 32, 32));
		walkDown.addFrame(sf::IntRect(224, 0, 32, 32));

		Animator pacManAnimator;
		pacManAnimator.addAnnimation("walkLeft", &walkLeft);
		pacManAnimator.addAnnimation("walkRight", &walkRight);
		pacManAnimator.addAnnimation("walkUp", &walkUp);
		pacManAnimator.addAnnimation("walkDown", &walkDown);

		sf::Texture fantomTexture;

		if (!fantomTexture.loadFromFile("sprites\\fantom.png")) {
			throw Error("Can't load fantom.png");
		}

		sf::Sprite fantomSprite;
		fantomSprite.setTexture(fantomTexture);

		Animation lesDents(&fantomSprite, 0.166666667);
		lesDents.addFrame(sf::IntRect(0, 0, 32, 32));
		lesDents.addFrame(sf::IntRect(32, 0, 32, 32));

		Animator fantomAnimator;
		fantomAnimator.addAnnimation("lesDents", &lesDents);

		fantomAnimator.setCurentAnimation("lesDents");

		//main loop
		sf::Clock clock;
		float angle = 0;
		fantomSprite.setOrigin(32.0f, 32.0f);

		while (window.isOpen()) {
			while (window.pollEvent(event)){
				switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					switch (event.key.code) {
						
					case sf::Keyboard::Q :
							pacManAnimator.setCurentAnimation("walkLeft");
							break;
					case sf::Keyboard::D :
							pacManAnimator.setCurentAnimation("walkRight");
							break;
					case sf::Keyboard::Z :
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


			window.clear();
			fantomAnimator.playAnnimation();
			window.draw(fantomSprite);
			fantomSprite.setPosition(fantomSprite.getPosition().x + clock.getElapsedTime().asSeconds() * 40.0f, 64.0f);
			fantomSprite.setRotation(angle);
			angle += clock.getElapsedTime().asSeconds() * 500.0f;
			window.display();

			cout << 1/clock.restart().asSeconds() << " fps"<< endl;
		}
	}
	catch (Error e) {
		cout << e << endl;
		system("pause");
		return -1;
	}

	return 0;
}