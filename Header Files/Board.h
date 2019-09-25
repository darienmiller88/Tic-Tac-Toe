#pragma once
#include <SFML/Graphics.hpp>
#include "Random.h"
#include <vector>
#include <functional>

//Since I am using sprites to represent the X and O in the window, I need some way to identify which sprite is which. "NOT_SET" is used
//determine whether or not a spot in the board has a game piece in it or not. I cannot really on the default spriteNames() because it
//defaults to 
enum class spriteNames{ 
	X_SPRITE, O_SPRITE, NOT_SET 
};

using GamePiece = std::pair<spriteNames, sf::Sprite>;

/**
* Class to represent the tic tac toe board. 
*/
class Board{

	//public functions
	public:
		Board();

		//Draws the board, as well as the sprites to the screen.
		void drawBoard(sf::RenderWindow &window);

		//Returns true or false based on whether or not all nine slots are filled.
		bool isFull();

		/*
		* @param gamePiece - a std::pair consisting of a spriteName and a sf::Sprite containing an x or O sprite
		* @param window - the window in which everything will be drawn to.
		* @param mousePosition - the global position of the mouse 
		*
		* This function will be called once the user clicks anywhere on the window, and the click will be handled accordingly. If the 
		* user clicks on any of the nine spots on the board, this function will place the game piece on that spot on the board.
		*
		*/
		bool handleUserClick(const GamePiece &gamePiece,  sf::RenderWindow &window, const sf::Vector2f &mousePosition);

		/*
		* @param gamePiece - a std::pair consisting of a spriteName and a sf::Sprite containing an x or O sprite
		* @param boardPosition - which box on the board the user wants to place their game piece in. For example, box 0, 0
		* is at the top left, box 1, 1 is in the middle, and box 2, 2 is at the bottom right.
		*
		* This function will take in a game piece, the position on the board it will go, and places it there.
		*
		*/
		void addPieceToBoard(const GamePiece &gamePiece, const sf::Vector2i &boardPosition);
		
		//temp
		void addPieceToBoard(const GamePiece &gamePiece);

		/*
		* This function will check every row, column and diagonal of the box for three of a kind, and return true or false based on whether
		* or 
		*/
		bool isGameWon(spriteNames spriteName);

		/*
		* This function will clear the board of all of the game pieces currently sitting on it.
		*/
		void clearBoard();

		void initialize(int windowWidth, int windowHeight);

	//Private functions
	private:

		/*
		* @param mousePosition -the global position of the mouse 
		*
		* @return value - A std::pair consisting of sf::Vector with an ordered pair describing which box the mouse cursor was in when a 
		* click was detected, and a bool which will hold true or false depending on whether or not the user clicked a mouse button.
		* 
		*/
		std::pair<sf::Vector2i, bool> getBox(const sf::Vector2f &mousePosition);
		
		
		void printBoard();

		/*
		* @param windowSize - the dimensions of the window
		*
		* This function will the determine the position of the midpoint of each of the nine boxes on the tic tac toe board, and store each
		* one in a two dimensional array.
		*/
		void determineMidPoints(const sf::Vector2u &windowSize);

		//private members
	private:

		sf::RectangleShape winnerLine;
		bool drawLine;

		//the texture needed for the board 
		sf::Texture boardTexture;
		sf::Sprite boardSprite;

		//Rather than making a 2D array of sprites, we will make it a pair, as to associate the sprite with either of the names in the
		//"spriteNames" enumerator. We are mapping a "SpriteName" to a sf::Sprite . We need to do all this BS because sf::Sprite doesn't
		//come with an == operator defined on it, so doing something like sf::Sprite board[3][3] would be IDEAL, but impossible since
		//we can't compare each spot when checking for a winner. Instead, well compare the sprite name to see if each spot has the same
		//name.
		GamePiece board[3][3];

		//2D array that will hold all the position of the midpoints of all of the boxes on the board. We need this information so we
		//can print each sprite in the middle of each box. Neatness matters!
		sf::Vector2f boxMidPoints[3][3];

		std::vector< std::pair< sf::Vector2u, sf::Vector2f> > openSpots;
		Random rand;
		int numFilledSpots;
};