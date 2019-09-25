#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "Board.h"
#include "GameState.h"

class TicTacToe : public GameState{
	public:
		void run(sf::RenderWindow &window) override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window) override;
		void pause() override;
		void unpause() override;
		void initialize(int windowWidth, int windowHeight) override;

		static TicTacToe &getInstance();
	private:
		TicTacToe() = default;
		void initializeSprites();
		void winConditions(bool isGameOver);
	private:
		sf::Clock clock;
		sf::Time elaspedTime;
		sf::Texture boardTexture, spriteSheetTexture;
		sf::Sprite boardSprite;
		GamePiece xSprite, oSprite, currentPlayer, previousPlayer;
		Board board;
		Random rand;
		const float PRINT_FREQUENCY = 0.5f;
};

