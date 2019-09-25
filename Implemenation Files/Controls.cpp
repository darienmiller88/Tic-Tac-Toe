#include "Controls.h"
#include "StateManager.h"
#include "TicTacToe.h"

void Controls::run(sf::RenderWindow &window){
	window.draw(backGroundSprite);
	window.draw(controls);
	window.draw(restartGame);
	window.draw(clickToPlace);
	window.draw(pressAnyKey);
	window.draw(goBackSprite);
	window.draw(backSpace);
}

void Controls::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window){
	if (e.type == e.KeyPressed)
		manager.pushState(&TicTacToe::getInstance());
	else if (e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left and isSpriteClicked(goBackSprite, window))
		manager.popState();
}

void Controls::pause(){

}

void Controls::unpause(){

}

void Controls::initialize(int windowWidth, int windowHeight){
	tryToReadFile(font, "C:\\Users\\Darien Miller\\Desktop\\fonts\\leadcoat.ttf");
	tryToReadFile(backGroundTexture, "images/background.jpg");
	tryToReadFile(goBackTexture, "images/home.png");

	backGroundTexture.setSmooth(true);
	goBackTexture.setSmooth(true);

	backGroundSprite.setTexture(backGroundTexture);
	goBackSprite.setTexture(goBackTexture);

	float xScale = static_cast<float>(windowWidth) / backGroundTexture.getSize().x;
	float yScale = static_cast<float>(windowHeight) / backGroundTexture.getSize().y;
	backGroundSprite.setScale(xScale, yScale);
	goBackSprite.setScale(1 / 8.f, 1 / 8.f);
	
	//Set the fonts to the texts
	controls.setFont(font);
	restartGame.setFont(font);
	clickToPlace.setFont(font);
	pressAnyKey.setFont(font);
	backSpace.setFont(font);

	//Set text colors
	controls.setFillColor(sf::Color::Black);
	restartGame.setFillColor(sf::Color::Black);
	clickToPlace.setFillColor(sf::Color::Black);
	pressAnyKey.setFillColor(sf::Color::Black);
	backSpace.setFillColor(sf::Color::Black);

	//set character sizes
	controls.setCharacterSize(70);
	restartGame.setCharacterSize(30);
	clickToPlace.setCharacterSize(30);
	pressAnyKey.setCharacterSize(50);
	backSpace.setCharacterSize(30);
	
	//Set the strings
	controls.setString("CONTROLS");
	restartGame.setString("SPACE - RESTART GAME");
	clickToPlace.setString("USE MOUSE TO CLICK A SPOT TO PLACE AN X OR O");
	pressAnyKey.setString("PRESS ANY KEY TO CONTINUE");
	backSpace.setString("BACKSPACE - GO BACK TO PREVIOUS SCREEN");

	//set positions
	controls.setPosition(windowWidth / 2 - controls.getGlobalBounds().width / 2, 0.f);
	restartGame.setPosition(0.f, windowHeight * (1/4.f));
	clickToPlace.setPosition(0.f, restartGame.getPosition().y + restartGame.getGlobalBounds().height * 2);
	backSpace.setPosition(0.f, clickToPlace.getPosition().y + clickToPlace.getGlobalBounds().height * 2);
	pressAnyKey.setPosition(windowWidth / 2 - pressAnyKey.getGlobalBounds().width / 2,  windowHeight - pressAnyKey.getGlobalBounds().height);
	goBackSprite.setPosition(0.f, 0.f);
}

Controls &Controls::getInstance(){
	static Controls c;
	return c;
}
