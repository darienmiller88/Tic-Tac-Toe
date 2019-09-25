#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class StateManager;

class GameState{
	public:
		//In order to force singleton behavior, we must disable the copy constructor, and assignment operator. 
		GameState& operator = (const GameState &state) = delete;
		GameState(const GameState &state) = delete;

		virtual ~GameState();

		//display the state to the screen
		virtual void run(sf::RenderWindow &window) = 0;

		//function to allow a gamestate to pause while another gamestate is running
		virtual void pause() = 0;
		
		//since we can pause game states, we also need to be able to unpause/resume them!
		virtual void unpause() = 0;

		//Purely virtual function to allow subclasses of the State class to handle mouse and keyboard input, and change states from
		//within their own state (for example, a title screen stating containing a menu with settings, play game, quit, etc.)
		virtual void handleInput(StateManager &manager, const sf::Event &e, const sf::RenderWindow &window) = 0;
		
		//function to allow a game state to initialize its members. Since we are using singleton classes, this cannot be done 
		//in a constructor, and must be done in this function.
		virtual void initialize(int windowWidth, int windowHeight) = 0;
		
	protected:
		//Utility function to read and error handle a file into a texture.
		template<class type>
		void tryToReadFile(type &texture, const std::string &fileName);
		
		//Function to let each gamestate signal to the gamestate manager to switch to another gamestate.
		void changeState(StateManager &manager, GameState *state);

		//function to allow gamestates to check if the mouse cursor is 
		bool isMouseTouching(const sf::Sprite &clickableSprite, const sf::RenderWindow &window) const;

		//function to allow gamestates to check if an sf::Text was clicked or not
		bool isSpriteClicked(const sf::Sprite &clickableSprite, const sf::RenderWindow &window) const;
		GameState(){}
};

template<class type>
inline void GameState::tryToReadFile(type &texture, const std::string &fileName){
	if (!texture.loadFromFile(fileName)) {
		std::cout << "Cannot read from file!\n";
		exit(1);
	}
}
