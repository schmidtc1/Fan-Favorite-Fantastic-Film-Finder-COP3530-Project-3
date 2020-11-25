#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <string>
#include <iostream>
#include "SpriteManager.h"
#include "TextureManager.h"

std::unordered_map<std::string, sf::Sprite> SpriteManager::sprites;

//======LOAD TEXTURE======//
//------Loads textures in the images folder from given name------//
void SpriteManager::loadSprite(const char* fileName)
{
	sprites[fileName] = sf::Sprite(TextureManager::getTexture(fileName));
}

//======GET TEXTURE======//
//------Returns texture of the given name------//
sf::Sprite& SpriteManager::getSprite(const char* key)
{
	if (sprites.find(key) == sprites.end())
	{
		std::cout << "MISSING SPRITE: " << key << std::endl;
	}
	return sprites[key];
}

//======CLEAR TEXTURES======//
//------Removes all textures from the map------//
void SpriteManager::clear()
{
	sprites.clear();
}