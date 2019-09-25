#pragma once
#include <SFML/Graphics.hpp>

class SFMLUtilities{
	public:
		SFMLUtilities();

		//Utility function to read and error handle a file into a texture.
		template<class type>
		void tryToReadFile(type &texture, const std::string &fileName);

		//function to allow gamestates to check if the mouse cursor is 
		bool isMouseTouching(const sf::Sprite &clickableSprite, const sf::RenderWindow &window) const;

		//function to allow gamestates to check if an sf::Text was clicked or not
		bool isSpriteClicked(const sf::Sprite &clickableSprite, const sf::RenderWindow &window) const;
		
		const sf::Text &createText(const std::string &word, const std::string &filePath, int charSize, const sf::Vector2f &pos, 
			const sf::Color &color, sf::Text::Style = sf::Text::Style());

};

template<class type>
inline void SFMLUtilities::tryToReadFile(type &texture, const std::string &fileName){

}
