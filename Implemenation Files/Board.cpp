#include "Board.h"
#include <iostream>
#include <cmath>

Board::Board() : numFilledSpots(0){
}

void Board::drawBoard(sf::RenderWindow &window){
	//draw the game board
	window.draw(boardSprite);

	//And the game pieces
	for (size_t row = 0; row < 3; row++)
		for (size_t column = 0; column < 3; column++) 
			window.draw(board[row][column].second);
	if(drawLine)
		window.draw(winnerLine);
}

bool Board::isFull(){
	return numFilledSpots >= 9;
}

bool Board::handleUserClick(const GamePiece &gamePiece, sf::RenderWindow &window, const sf::Vector2f &mousePosition){
	auto box = getBox(mousePosition);
	
	if (box.second and board[box.first.x][box.first.y].first == spriteNames::NOT_SET){
		addPieceToBoard(gamePiece, box.first);
		
		//return true when a game piece was successfully added to the board.
		return true;
	}

	//return false otherwise!
	return false;
}

void Board::addPieceToBoard(const GamePiece &gamePiece, const sf::Vector2i &position){
	//We will utilize both the 2D array of sprites and the 2D array of sf:: Vector2f objects to determine the layout of the board
	//in the window. First, add the gamePiece(sprite) to the 2D array of sprites. Afterwards, find the associaitve position in
	//in the array of midpoints, and set the recently added game piece to the position retrieved from the array of midpoints.
	board[position.x][position.y] = gamePiece;
	board[position.x][position.y].second.setPosition(boxMidPoints[position.x][position.y]);
	numFilledSpots++;
	printBoard();
}

void Board::addPieceToBoard(const GamePiece &gamePiece){
	int index = rand.getIntInRange(0, openSpots.size());
	sf::Vector2u boardPosition = openSpots[index].first;
	sf::Vector2f midPointPosition = openSpots[index].second;
	
	board[boardPosition.x][boardPosition.y] = gamePiece;
	board[boardPosition.x][boardPosition.y].second.setPosition(midPointPosition.x, midPointPosition.y);

	openSpots.erase( openSpots.begin() + index );                                                             
	numFilledSpots++;
}

bool Board::isGameWon(spriteNames spriteName){

	auto checkForThree = [&](spriteNames first, spriteNames second, spriteNames third) {
		return first == second and second == third and first != spriteNames::NOT_SET;
	};
	
	//check each row for a win
	for (size_t row = 0; row < 3; row++){
		//We will check each position in the first row of each players boolean board to see if each position is true, 
		//AND if they all have the same name (same sprite name). 
		
		if (checkForThree(board[row][0].first, board[row][1].first, board[row][2].first)) {
			drawLine = true;
			winnerLine.setPosition(boxMidPoints[row][1]);	

			return true;
		}
	}

	//cheack columns for a win
	for (size_t column = 0; column < 3; column++){
		if (checkForThree(board[0][column].first, board[1][column].first, board[2][column].first)) {
			drawLine = true;
			winnerLine.setRotation(90);
			winnerLine.setPosition(boxMidPoints[1][column]);
			return true;
		}	
	}

	//check for both diagonals
	if (checkForThree(board[0][0].first, board[1][1].first, board[2][2].first)) {
		drawLine = true;
		winnerLine.setRotation(45);
		winnerLine.setPosition(boxMidPoints[1][1]);

		return true;
	}else if (checkForThree(board[2][0].first, board[1][1].first, board[0][2].first)) {
		drawLine = true;
		winnerLine.setRotation(-45);
		winnerLine.setPosition(boxMidPoints[1][1]);

		return true;
	}
		
	return false;
}

void Board::clearBoard(){
	openSpots.clear();

	for (size_t row = 0; row < 3; row++) 
		for (size_t column = 0; column < 3; column++) {
			openSpots.push_back({ {row, column}, boxMidPoints[row][column] });
			board[row][column] = std::make_pair(spriteNames::NOT_SET, sf::Sprite());
		}
	drawLine = false;
	numFilledSpots = 0;
	system("cls");
}

void Board::initialize(int windowWidth, int windowHeight){
	if (!boardTexture.loadFromFile("images/newBoard.png")) {
		std::cerr << "Could not read from file!\n";
		exit(1);
	}
	drawLine = false;

	boardTexture.setSmooth(true);
	boardSprite.setTexture(boardTexture);

	float xScale = static_cast<float>(windowWidth) / boardTexture.getSize().x;
	float yScale = static_cast<float>(windowHeight) / boardTexture.getSize().y;
	boardSprite.setScale(xScale, yScale);
	determineMidPoints( {static_cast<size_t>(windowWidth), static_cast<size_t>(windowHeight)} );

	winnerLine.setSize(sf::Vector2f(sqrt(windowHeight * windowHeight + windowHeight * windowHeight), 15.f));
	winnerLine.setOrigin(winnerLine.getSize().x / 2.f, winnerLine.getSize().y / 2.f);
	winnerLine.setFillColor(sf::Color::Black);
}

//This function will translate the mouse position to a box on the board, and return the box that the users mouse is residing in.
std::pair<sf::Vector2i, bool> Board::getBox(const sf::Vector2f &mousePosition){
	//In order to find out which box the user clicked, we will need to find out how wide each box is in terms of pixels. We found this out
	//in the "determineMidPoints member function, so all we do is reference the midpoitn position of box 0,0 (top left). We will only use
	//half the box width however, since we are using the midpoints as the starting point (if you start in the middle of a square, as long
	//you know half the width, you will be able to find the position of the outer edge of the square!).
	float halfBoxWidth = boxMidPoints[0][0].x;

	//utility lambda to reduce the amount of comparisons I have to make in the nested for loop below. It will take either the x or y
	//position of the mouse, and of the midpoint to see if that mouse coord falls in the range from where the box starts to where it ends
	//For example, take the first box, 0, 0 (top left). This box's x position starts 0, and goes to roughly 95 pixels, same with the y. 
	//We want to see if the x position of the mouse falls in the range of x = 0 and x = 90, and if the y position of the box also falls
	//in the range y = 0, and y = 90;
	auto isInABox = [&](float mouseChoord, float midPointChoord) {
		return (mouseChoord <= midPointChoord + halfBoxWidth and mouseChoord >= midPointChoord - halfBoxWidth);
	};

	for (size_t row = 0; row < 3; row++) {
		for (size_t column = 0; column < 3; column++) {
			//if the mouse position falls in the range of any of the nine boxes, return a pair containing the which box was chosen,
			//as well a boolean(true) to signal that the mouse position was in a valid spot.
			if (isInABox(mousePosition.x, boxMidPoints[row][column].x) and isInABox(mousePosition.y, boxMidPoints[row][column].y)) {
				return std::make_pair(sf::Vector2i(row, column), true);
			}
		}
	}
	//if the mouse position was NOT in a valid box, return a pair with an empty Vector2i and false to signal that the mouse was NOT in a
	//valid box. We need to return a pair because the function calling this one needs to know two bits of information:
	//1. which box the mouse position was in, so it can index into the board array using the coordinates
	//2. whether or not the mouse was even in a box to begin.
	//It would be nice to be able to just send the a default sf::Vector2i, but the problem with that is the default vector contains 0 for 
	//the x and y values, and (0, 0) is a valid box!
	return std::make_pair(sf::Vector2i(), false);
}

void Board::printBoard(){
	for (size_t row = 0; row < 3; row++) {
		for (size_t column = 0; column < 3; column++) {
			if (board[row][column].first == spriteNames::X_SPRITE)
				std::cout << "x\t";
			else if (board[row][column].first == spriteNames::O_SPRITE)
				std::cout << "o\t";
			else
				std::cout << "-\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void Board::determineMidPoints(const sf::Vector2u &windowSize){
	//Using outside information, I found out that the width of the board image I am using is 23 times as wide as the borders seperating 
	//each box. So in order to find the width of this border, simply perform the the following division.
	float borderWidth = windowSize.x / 23.f;

	//Since we know how wide the image is In order to find the 
	float boxWidth = (windowSize.x - (2 * borderWidth)) / 3.f;

	//We first find the midpoint of the first box, the one in the upperleft corner. As a result of the top left corner
	//of the screen being (0, 0), the first box midpoint will simply be the middle of the first one. 
	sf::Vector2f currentPosition = { boxWidth / 2, boxWidth / 2 };
	
	for (size_t row = 0; row < 3; row++){
		for (size_t column = 0; column < 3; column ++){
			//We will add the midpoint to the appropiate spot in the 2D array.
			boxMidPoints[row][column] = currentPosition;

			//initialize every "first" value in the 2D board array to "NOT_SET"
			board[row][column].first = spriteNames::NOT_SET;
			openSpots.push_back({ {row, column}, currentPosition });

			//Afterwards, shift over to the next box in the row by keeping the y position the same, and adding to the x position.
			currentPosition.x += boxWidth + borderWidth;		
		}

		//Finally, set the x position back to midpoint of the first column, but shift the y position over to the next row.
		currentPosition = { boxWidth / 2, currentPosition.y + (boxWidth + borderWidth) };
	}

	for (size_t row = 0; row < 3; row++) {
		for (size_t column = 0; column < 3; column++)
			std::cout << "(" << boxMidPoints[row][column].x << ", " << boxMidPoints[row][column].y << ")\t";
		std::cout << "\n";
	}
}
