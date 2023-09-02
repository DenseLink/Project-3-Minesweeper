#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
using std::map;
using std::string;

class TextureManager
{
	//one and only one of these in memory because of static
	static map<string, sf::Texture> textures;
	static void LoadTexture(string textureName);
public:

	static sf::Texture& GetTexture(string textureName);
	static void Clear();
};

