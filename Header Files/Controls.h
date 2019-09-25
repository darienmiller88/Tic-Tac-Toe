#pragma once
#include "GameState.h"

class Controls : public GameState{
	public:
		void run(sf::RenderWindow &window) override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window) override;
		void pause() override;
		void unpause() override;
		void initialize(int windowWidth, int windowHeight) override;

		static Controls &getInstance();
	private:

		//We have to hide the default constructor to prevent the user trying to instatiate this class
		Controls() = default;
	private:
		sf::Font font;
		sf::Text controls, restartGame, clickToPlace, pressAnyKey, backSpace;
		sf::Texture backGroundTexture, goBackTexture;
		sf::Sprite backGroundSprite, goBackSprite;
};

