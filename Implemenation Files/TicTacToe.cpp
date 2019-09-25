 #include "TicTacToe.h"
#include "StateManager.h"
#include <iostream>

void TicTacToe::run(sf::RenderWindow &window){
	elaspedTime += clock.getElapsedTime();
	clock.restart();
	board.drawBoard(window);
	winConditions(board.isGameWon(currentPlayer.first));
}
 
void TicTacToe::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window){
	if (e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left and !board.isGameWon(currentPlayer.first)) {
		//if the user clicks the left button when the game is still in play, AND the follwing function returns true, which
		//signifies that the user clicked a valied spot on the board, swap the current and previous players.
		if (board.handleUserClick(currentPlayer, const_cast<sf::RenderWindow&>(window),
			window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
			std::cout << "piece added!\n";
			std::swap(currentPlayer, previousPlayer);
		}
	}
	else if (e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::BackSpace)
		manager.popState();
}

void TicTacToe::pause(){

}

void TicTacToe::unpause(){

}

void TicTacToe::initialize(int windowWidth, int windowHeight){
	tryToReadFile(spriteSheetTexture, "images/xAndo.png");

	spriteSheetTexture.setSmooth(true);
	xSprite.second.setTexture(spriteSheetTexture);
	oSprite.second.setTexture(spriteSheetTexture);
	initializeSprites();
	board.initialize(windowWidth, windowHeight);

	currentPlayer = (Random().getIntInRange(0, 2) == 0) ? xSprite : oSprite;
	previousPlayer = (currentPlayer.first == xSprite.first) ? oSprite : xSprite;
}

TicTacToe &TicTacToe::getInstance(){
	static TicTacToe t;
	return t;
}

void TicTacToe::initializeSprites(){
	xSprite.first = spriteNames::X_SPRITE;
	oSprite.first = spriteNames::O_SPRITE;

	sf::Vector2u textureSize = spriteSheetTexture.getSize();
	
	//On the sprite sheet being used for the X and O sprites, it is a 2 x 2 sheet, so to get the length and width of each sprite,  
	//I have to divide the length and width of the sprite sheet by the number of sprites on each dimension.
	textureSize.x /= 2;
	textureSize.y /= 2;

	//The sprite sheet contains the x and y sprites needed for this game. Here, I am parsing the sheet to get only one sprite from it
	//by specyifing which image in it I am taking, and how much of it I want.
	xSprite.second.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y - 5));
	oSprite.second.setTextureRect(sf::IntRect(textureSize.x * 1, textureSize.y * 0, textureSize.x, textureSize.y));

	//Set the origin of the sprite to be in the middle rather than the top left corner. This wil make it much easier to print the sprite
	//onto the game board.
	xSprite.second.setOrigin(sf::Vector2f(xSprite.second.getGlobalBounds().width / 2, xSprite.second.getGlobalBounds().height / 2));
	oSprite.second.setOrigin(sf::Vector2f(oSprite.second.getGlobalBounds().width / 2, oSprite.second.getGlobalBounds().height / 2));
}

void TicTacToe::winConditions(bool isGameOver){
	//If the user clicks the space button, clear the board and reset the game.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		board.clearBoard();
	}
	else if (isGameOver and previousPlayer.first == spriteNames::O_SPRITE) {
		if (elaspedTime.asSeconds() >= PRINT_FREQUENCY) {
			std::cout << "O won!\n ";
			elaspedTime = sf::Time();
		}
		//when the player using the O sprite wins, set the current player to the x sprite.
		currentPlayer = xSprite, previousPlayer = oSprite;
	}
	else if (isGameOver and previousPlayer.first == spriteNames::X_SPRITE) {
		if (elaspedTime.asSeconds() >= PRINT_FREQUENCY) {
			std::cout << "X won!\n";
			elaspedTime = sf::Time();
		}
		currentPlayer = oSprite, previousPlayer = xSprite;
	}
	else if (board.isFull()) {
		if (elaspedTime.asSeconds() >= PRINT_FREQUENCY) {
			std::cout << "DRAW\n";
			elaspedTime = sf::Time();
		}
		std::swap(currentPlayer, previousPlayer);
	}
}