#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class SpriteManager
{
private:
	static std::unordered_map<std::string, sf::Sprite> sprites;

public:
	static void loadSprite(const char* fileName);
	static sf::Sprite& getSprite(const char* key);
	static void clear();
};