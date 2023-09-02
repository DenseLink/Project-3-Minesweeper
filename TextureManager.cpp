#include "TextureManager.h"

map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName)
{
	string path = "/images/"; //images/
	path += textureName; //images/dino
	path += ".png"; //images/dino.png
	textures[textureName].loadFromFile(path);
}
sf::Texture& TextureManager::GetTexture(string textureName)
{
	//1. check if the texture isn't loaded
	if (textures.find(textureName) == textures.end())
	{

		//1 a. if not, load it
		LoadTexture(textureName);
	}
	//2. return the texture (wheter it was just loaded, or already previously loaded)
	return textures[textureName];
}
void TextureManager::Clear()
{
	textures.clear();
}