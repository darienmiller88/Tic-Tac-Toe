#include "GameState.h"
#include "StateManager.h"

void GameState::changeState(StateManager &manager, GameState *state){
	manager.changeState(state);
}

bool GameState::isMouseTouching(const sf::Sprite& clickableSprite, const sf::RenderWindow& window) const{
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	
	return clickableSprite.getGlobalBounds().contains(mousePosition);
}

bool GameState::isSpriteClicked(const sf::Sprite &clickableSprite, const sf::RenderWindow &window) const{
	//This statement will return true if the left mouse button was clicked, and if the mouse cursor was within the bounds of
	//the rectangle surrounding the Sprite object.
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left) and isMouseTouching(clickableSprite, window));
}

GameState::~GameState()
{
}
