#pragma once
#include "GameState.h"
#include <stack>
#include <SFML/Graphics.hpp>

class StateManager{
	public:
		StateManager(int windowWidth, int windowHeight, const std::string &title);
		void runGame();
		void quitGame();
		void pushState(GameState *state);
		void changeState(GameState *state);
		void popState();
	private:
		sf::Clock clock;
		std::stack<GameState*> states;
		bool gameIsRunning;
		sf::RenderWindow window;
};

