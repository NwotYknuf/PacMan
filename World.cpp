#include "World.h"

const int HEAT_DECAY = 0.001;

World::World(
	sf::RenderWindow * window, 
	Graph<EdgeInfo, VerticeInfo>* graph, 
	DrawGraph<EdgeInfo, VerticeInfo>* drawGraph, 
	Actor<GCharacter<VerticeInfo, EdgeInfo, PacmanInfo>, 
	PacmanBehavior<VerticeInfo, EdgeInfo, PacmanInfo>, 
	DrawCharacter<VerticeInfo, EdgeInfo, PacmanInfo>>* pacman,
	sf::Font * _font,
	WorldToScreen & transform) : _transform(transform) {
	_window = window;
	_graph = graph;
	_drawGraph = drawGraph;
	_pacman = pacman;
	font = _font;
}

World::~World()
{
}

void World::addFantom(Actor<GCharacter<VerticeInfo, EdgeInfo, FantomInfo>, FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>, DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>>* fantom){
	_fantoms.push_back(fantom);
}

int World::nbrOfPacgoms() {
	int total = 0;

	PElement<Vertice<VerticeInfo>> * temp = _graph->lVertices;

	while (temp != NULL) {
		total++;
		temp = temp->next;
	}

	PElement<Edge<EdgeInfo, VerticeInfo>> * temp1 = _graph->lEdges;
	while (temp1 != NULL) {
		total++;
		temp1 = temp1->next;
	}

	return total;
}

void World::init() {
	clock = GameClock::getInstance();
	maxScore = nbrOfPacgoms();

	gameOverText.setString("GAME OVER");
	gameOverText.setFont(*font);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2, gameOverText.getGlobalBounds().height / 2);
	gameOverText.setScale(sf::Vector2f(2, 2));
	gameOverText.setPosition(_transform(sf::Vector2<float>(6.0f, 7.0f)));
}

void World::updateGraph() {		
	PElement<Edge<EdgeInfo, VerticeInfo>> * temp = _graph->lEdges;

	while (temp != NULL) {
		if (temp->value->value.heat > 0)
			temp->value->value.heat -= HEAT_DECAY;
		temp = temp->next;
	}
}

void World::handleEvents() {
	while (_window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			_window->close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {

			case sf::Keyboard::Numpad4:
			case sf::Keyboard::Numpad6:
			case sf::Keyboard::Numpad8:
			case sf::Keyboard::Numpad2:
			case sf::Keyboard::Numpad1:
			case sf::Keyboard::Numpad3:
			case sf::Keyboard::Numpad7:
			case sf::Keyboard::Numpad9:
				_pacman->setLastInput(event.key.code);
				break;
			}
			break;
		default:
			break;
		}
	}
}

void World::updateMain() {
	if (clock->getElapsedTime() >= 0.016666666f) {
		_window->clear();

		updateGraph();
		AStarTools::target = _pacman->getPosition<VerticeInfo>();
		_drawGraph->update();
		_graph->draw(*_drawGraph);


		bool check = false;
		for (Actor<
			GCharacter<VerticeInfo, EdgeInfo, FantomInfo>,
			FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>,
			DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>
		> * fantom : _fantoms) {
			fantom->update();
			if (fantom->getPosition<VerticeInfo>() == _pacman->getPosition<VerticeInfo>()) {
				check = true;
			}
		}
		_pacman->update();

		_window->display();
		
		if (check) {
			end = true;
			_pacman->getGchar()->info.alive = false;
			_pacman->resetAnimator();
		}

		int score = _pacman->getGchar()->info.score;

		if (score % maxScore == 0 && score != 0) {
			end = true;
		}

		clock->restart();
	}
}

void World::updateGameOver() {
	if (clock->getElapsedTime() >= 0.016666666f) {
		_window->clear();

		updateGraph();
		AStarTools::target = _pacman->getPosition<VerticeInfo>();
		_drawGraph->update();
		_graph->draw(*_drawGraph);

		for (Actor<
			GCharacter<VerticeInfo, EdgeInfo, FantomInfo>,
			FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>,
			DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>
		> * fantom : _fantoms) {
			fantom->updateEndGame();
		}

		_pacman->updateEndGame();

		if (elapsedTime > 2.0f)
			_window->draw(gameOverText);

		_window->display();

		elapsedTime += clock->getElapsedTime();
		clock->restart();

	}
}

void World::updateWin() { }

void World::resetGraph(){
	PElement<Edge<EdgeInfo, VerticeInfo>> * temp = _graph->lEdges;

	while (temp != NULL) {
		temp->value->value.reset();
		temp = temp->next;
	}

	PElement<Vertice<VerticeInfo>> * temp2 = _graph->lVertices;

	while (temp2 != NULL) {
		temp2->value->value.info.reset();
		temp2 = temp2->next;
	}

}

void World::reset() {
	end = false;
	resetGraph();
	_pacman->reset();

	for (Actor<
	GCharacter<VerticeInfo, EdgeInfo, FantomInfo>,
	FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>,
	DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>
	> * fantom : _fantoms) {
	fantom->reset();
	}
}

void World::update() {

	handleEvents();

	if (!end) {
		updateMain();
	}
	else {

		if (elapsedTime < 4.0f) {
			if (_pacman->getGchar()->info.alive)
				updateWin();
			else {
				_pacman->setAnimation("explode");
				updateGameOver();
			}
		}
		else {
			elapsedTime = 0.0f;
			reset();
		}
	}
}
