#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class AssetManager{
	public:


	private:
		std::unordered_map<std::string, sf::Text> texts;
		std::unordered_map<std::string, sf::Texture> textures;
};

