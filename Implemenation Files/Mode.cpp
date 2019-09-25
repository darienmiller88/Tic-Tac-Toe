#include "Mode.h"
#include "StateManager.h"
#include "Controls.h"

void Mode::run(sf::RenderWindow &window){
	window.draw(backgroundSprite);
	window.draw(selectMode);
	window.draw(normalSprite);
	window.draw(hardSprite);
	window.draw(lunaticSprite);
	window.draw(goBackSprite);
}

void Mode::handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window){
	bool isButtonClicked = e.type == e.MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left;
	
	if (isButtonClicked and isSpriteClicked(goBackSprite, window))
		manager.popState();
	else if (isButtonClicked and isSpriteClicked(normalSprite, window)) {
		currentSetting = DifficultySettings::NORMAL;
		std::cout << "normal mode\n";
		manager.pushState(&Controls::getInstance());
	}
	else if (isButtonClicked and isSpriteClicked(hardSprite, window)) {
		currentSetting = DifficultySettings::HARD;
		std::cout << "hard mode\n";
		manager.pushState(&Controls::getInstance());
	}
	else if (isButtonClicked and isSpriteClicked(lunaticSprite, window)) {
		currentSetting = DifficultySettings::LUNATIC;
		std::cout << "lunatic mode\n";
		manager.pushState(&Controls::getInstance());
	}
}

void Mode::pause(){
	std::cout << "Paused\n";
}

void Mode::unpause(){
	std::cout << "unpaused\n";
}

void Mode::initialize(int windowWidth, int windowHeight){
	//Read in all of the necessary files
	tryToReadFile(backgroundTexture, "images/background.jpg");
	tryToReadFile(font, "C:\\Users\\Darien Miller\\Desktop\\fonts\\leadcoat.ttf");
	tryToReadFile(normalTexture, "images/r_normal.png");
	tryToReadFile(hardTexture, "images/r_hard.png");
	tryToReadFile(lunaticTexture, "images/r_lunatic.png");
	tryToReadFile(goBackTexture, "images/home.png");

	//set all textures to smooth
	backgroundTexture.setSmooth(true);
	normalTexture.setSmooth(true);
	hardTexture.setSmooth(true);
	lunaticTexture.setSmooth(true);
	goBackTexture.setSmooth(true);

	//set textures to sprites
	backgroundSprite.setTexture(backgroundTexture);
	normalSprite.setTexture(normalTexture);
	hardSprite.setTexture(hardTexture);
	lunaticSprite.setTexture(lunaticTexture);
	goBackSprite.setTexture(goBackTexture);

	//Modify the text and add the necessary fields.
	selectMode.setFont(font);
	selectMode.setFillColor(sf::Color::Black);
	selectMode.setString("- SELECT MODE:");
	selectMode.setCharacterSize(70);
	selectMode.setOrigin(selectMode.getGlobalBounds().width / 2.f, selectMode.getGlobalBounds().height / 2.f);
	selectMode.setPosition(windowWidth / 2.f, selectMode.getGlobalBounds().height);

	//set scales
	float xScale = static_cast<float>(windowWidth) / backgroundTexture.getSize().x;
	float yScale = static_cast<float>(windowHeight) / backgroundTexture.getSize().y;
	backgroundSprite.setScale(xScale, yScale);
	goBackSprite.setScale(1/8.f, 1/8.f);

	//set sprite positions
	normalSprite.setPosition(windowWidth / 2 - normalSprite.getGlobalBounds().width / 2, windowHeight / 2.f);
	hardSprite.setPosition(normalSprite.getPosition().x, normalSprite.getPosition().y + 100);
	lunaticSprite.setPosition(normalSprite.getPosition().x, hardSprite.getPosition().y + 100);
	goBackSprite.setPosition(0.f, 0.f);

	currentSetting = DifficultySettings();
}

DifficultySettings Mode::getCurrentSetting() const{
	return currentSetting;
}

Mode &Mode::getInstance(){
	static Mode m;
	return m;
}
