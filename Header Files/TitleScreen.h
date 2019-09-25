#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

class TitleScreen : public GameState{
	public:
		void run(sf::RenderWindow &window) override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window) override;
		void pause() override;
		void unpause() override;
		void initialize(int windowWidth, int windowHeight) override;
		
		static TitleScreen &getInstance();
	private:

		//We have to hide the default constructor to prevent the user trying to instatiate this class
		TitleScreen() = default;
	private:
		sf::Texture backgroundTexture, titleTexture, onePlayerTexture, twoPlayerTexture, quitTexture;
		sf::Sprite backgroundSprite, titleSprite, onePlayerSprite, twoPlayerSprite, quitSprite;
};