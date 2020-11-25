#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
class TextureManager
{
private:
	static std::unordered_map<std::string, sf::Texture> textures;
public:
	static void loadTexture(const char* fileName);
	static sf::Texture& getTexture(const char* key);
	static void clear();
};

