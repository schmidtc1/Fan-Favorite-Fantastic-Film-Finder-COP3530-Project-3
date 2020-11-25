#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <string>
#include <iostream>
#include "TextureManager.h"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

//======LOAD TEXTURE======//
//------Loads textures in the images folder from given name------//
void TextureManager::loadTexture(const char* fileName)
{
	std::string filePath = "images/";
	filePath += fileName;
	filePath += ".png";
	textures[fileName].loadFromFile(filePath);
}

//======GET TEXTURE======//
//------Returns texture of the given name------//
sf::Texture& TextureManager::getTexture(const char* key)
{
	if (textures.find(key) == textures.end())
	{
		std::cout << "MISSING TEXTURE: " << key << ".png" << std::endl;
	}
	return textures[key];
}

//======CLEAR TEXTURES======//
//------Removes all textures from the map------//
void TextureManager::clear()
{
	textures.clear();
}