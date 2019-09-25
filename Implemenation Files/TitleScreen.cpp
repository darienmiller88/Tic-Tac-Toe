#include "TitleScreen.h"
#include "StateManager.h"
#include "Controls.h"
#include "Mode.h"
#include <iostream>

void TitleScreen::run(sf::RenderWindow &window){
	window.draw(backgroundSprite);
	window.draw(titleSprite);
	window.draw(onePlayerSprite);
	window.draw(twoPlayerSprite);
	window.draw(quitSprite);
}

void TitleScreen::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window){
	if (e.type == e.MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left and isSpriteClicked(onePlayerSprite, window)) 
		manager.pushState(&Mode::getInstance());
	else if (e.type == e.MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left and isSpriteClicked(twoPlayerSprite, window))
		manager.pushState(&Controls::getInstance());
	else if (e.type == e.MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left and isSpriteClicked(quitSprite, window))
		manager.quitGame();
}

void TitleScreen::pause(){

}

void TitleScreen::unpause(){

}

void TitleScreen::initialize(int windowWidth, int windowHeight){
	tryToReadFile(backgroundTexture, "images/background.jpg");
	tryToReadFile(onePlayerTexture, "images/onePlayer.png");
	tryToReadFile(twoPlayerTexture, "images/twoPlayer.png");
	tryToReadFile(titleTexture, "images/gameTitle.png");
	tryToReadFile(quitTexture, "images/quit.png");

	//set all the textures to smooth
	backgroundTexture.setSmooth(true);
	titleTexture.setSmooth(true);
	onePlayerTexture.setSmooth(true);
	twoPlayerTexture.setSmooth(true);
	quitTexture.setSmooth(true);

	//Assign each texture to their respective sprite
	backgroundSprite.setTexture(backgroundTexture);
	onePlayerSprite.setTexture(onePlayerTexture);
	twoPlayerSprite.setTexture(twoPlayerTexture);
	titleSprite.setTexture(titleTexture);
	quitSprite.setTexture(quitTexture);

	
	//Set the scale of the title sprite to match that of the window dimensions perfectly. By dividing the window dimensions by the title
	//texture dimensions, you will get the number that you have to multiply the titleTexture dimensions by to match the window dimensions.
	float xScale = static_cast<float>(windowWidth) / backgroundTexture.getSize().x;
	float yScale = static_cast<float>(windowHeight) / backgroundTexture.getSize().y;
	backgroundSprite.setScale(xScale, yScale);
	onePlayerSprite.setScale(0.25, 0.25);
	twoPlayerSprite.setScale(0.25, 0.25);
	quitSprite.setScale(1/6.f, 1/6.f);
	titleSprite.setScale(static_cast<float>(windowWidth) / titleTexture.getSize().x, 1);

	//Set the position of the one player and two player sprites
	onePlayerSprite.setPosition(0.f, windowHeight - onePlayerSprite.getGlobalBounds().height);
	twoPlayerSprite.setPosition(windowWidth - twoPlayerSprite.getGlobalBounds().width, windowHeight - twoPlayerSprite.getGlobalBounds().height);
	quitSprite.setPosition(windowWidth / 2 - quitSprite.getGlobalBounds().width / 2, windowHeight - quitSprite.getGlobalBounds().height);
	//quitSprite.setPosition(windowWidth  - quitSprite.getGlobalBounds().width / 2.f, windowHeight - quitSprite.getGlobalBounds().height);
	//onePlayerSprite.setColor(sf::Color::Yellow);
	//twoPlayerSprite.setColor(sf::Color::Green);
}

TitleScreen &TitleScreen::getInstance(){
	static TitleScreen t;
	return t;
}