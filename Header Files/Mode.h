#pragma once

#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>

enum class DifficultySettings
{ 
	NORMAL,
	HARD,
	LUNATIC
};

class Mode : public GameState {
	public:
		void run(sf::RenderWindow &window) override;
		void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window) override;
		void pause() override;
		void unpause() override;
		void initialize(int windowWidth, int windowHeight) override;
		DifficultySettings getCurrentSetting() const;

		static Mode &getInstance();
	private:

		//We have to hide the default constructor to prevent the user trying to instatiate this class
		Mode() = default;
	private:
		DifficultySettings currentSetting;
		sf::Font font;
		sf::Text selectMode;
		sf::Texture backgroundTexture, normalTexture, hardTexture, lunaticTexture, goBackTexture;
		sf::Sprite backgroundSprite, normalSprite, hardSprite, lunaticSprite, goBackSprite;
};