#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
#pragma once
using namespace std;
class Tile : public sf::Sprite
{


	sf::Sprite ourSprite;
	sf::Texture texture;
	//	float rotationRate;
public:
	bool isMine;
	bool isHidden;
	bool hasFlag;
	bool revealTile;
	bool resetTile;
	bool debug;
	bool Ones;
	bool Tens;
	bool Hundreds;
	bool Thousands;
	bool Negative;
	bool test1;
	bool test2;
	bool test3;
	bool victory;
	bool defeat;
	int number;
	bool numberone;
	//bool numbertwo;
	//bool numberthree;
	//bool numberfour;
	//bool numberfive;
	//bool numbersix;
	//bool numberseven;
	//bool numbereight;
	int onesposition;
	int tensposition;
	int hundredsposition;
	void Draw(sf::RenderWindow& window, int xPos, int yPos)
	{
		//isHidden = true;
		//isMine = true;
		if (numberone == true)
		{
			ourSprite.setPosition(xPos, yPos);
			if (number == 1) { ourSprite.setTexture(TextureManager::GetTexture("number_1")); }
			if (number == 2) { ourSprite.setTexture(TextureManager::GetTexture("number_2")); }
			if (number == 3) { ourSprite.setTexture(TextureManager::GetTexture("number_3")); }
			if (number == 4) { ourSprite.setTexture(TextureManager::GetTexture("number_4")); }
			if (number == 5) { ourSprite.setTexture(TextureManager::GetTexture("number_5")); }
			if (number == 6) { ourSprite.setTexture(TextureManager::GetTexture("number_6")); }
			if (number == 7) { ourSprite.setTexture(TextureManager::GetTexture("number_7")); }
			if (number == 8) { ourSprite.setTexture(TextureManager::GetTexture("number_8")); }
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}

		if (defeat == true)
		{
			ourSprite.setPosition(xPos, yPos);
			ourSprite.setTexture(TextureManager::GetTexture("face_lose"));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (victory == true)
		{
			ourSprite.setPosition(xPos, yPos);
			ourSprite.setTexture(TextureManager::GetTexture("face_win"));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (test1 == true)
		{
			ourSprite.setPosition(xPos, yPos);
			ourSprite.setTexture(TextureManager::GetTexture("test_1"));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (test2 == true)
		{
			ourSprite.setPosition(xPos, yPos);
			ourSprite.setTexture(TextureManager::GetTexture("test_2"));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (test3 == true)
		{
			ourSprite.setPosition(xPos, yPos);
			ourSprite.setTexture(TextureManager::GetTexture("test_3"));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (Ones == true)
		{
			ourSprite.setPosition(xPos, yPos);
			//this->setPosition.getPosition();
			ourSprite.setTexture(TextureManager::GetTexture("digits"));
			//ourSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
			ourSprite.setTextureRect(sf::IntRect((abs(21 * onesposition)), 0, 21, 32));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (Tens == true)
		{
			ourSprite.setPosition(xPos, yPos);
			//this->setPosition.getPosition();
			ourSprite.setTexture(TextureManager::GetTexture("digits"));
			//ourSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
			ourSprite.setTextureRect(sf::IntRect((abs(21 * tensposition)), 0, 21, 32));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (Hundreds == true)
		{
			ourSprite.setPosition(xPos, yPos);
			//this->setPosition.getPosition();
			ourSprite.setTexture(TextureManager::GetTexture("digits"));
			//ourSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
			ourSprite.setTextureRect(sf::IntRect((abs(21 * hundredsposition)), 0, 21, 32));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (Thousands == true && Negative == true)
		{
			ourSprite.setPosition(xPos, yPos);
			//this->setPosition.getPosition();
			ourSprite.setTexture(TextureManager::GetTexture("digits"));
			ourSprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (resetTile == true)
		{
			ourSprite.setPosition(xPos, yPos);
			//this->setPosition.getPosition();
			ourSprite.setTexture(TextureManager::GetTexture("face_happy"));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (debug == true)
		{
			ourSprite.setPosition(xPos, yPos);
			//this->setPosition.getPosition();
			ourSprite.setTexture(TextureManager::GetTexture("debug"));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		if (isHidden == true)
		{
			ourSprite.setPosition(xPos, yPos);
			//this->setPosition.getPosition();
			ourSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
			auto rect = getTextureRect();
			window.draw(ourSprite);
		}
		else
		{
			if (isMine == true)
			{
				ourSprite.setPosition(xPos, yPos);
				ourSprite.setTexture(TextureManager::GetTexture("tile_revealed"));
				window.draw(ourSprite);
				ourSprite.setTexture(TextureManager::GetTexture("mine"));
				window.draw(ourSprite);
			}
			else if (revealTile == true)
			{
				ourSprite.setPosition(xPos, yPos);
				ourSprite.setTexture(TextureManager::GetTexture("tile_revealed"));
				window.draw(ourSprite);
			}
			else if (hasFlag == true)
			{
				ourSprite.setPosition(xPos, yPos);
				ourSprite.setTexture(TextureManager::GetTexture("flag"));
				window.draw(ourSprite);
			}
		}

	}
	//struct Tile
	//{
	Tile* one = nullptr;
	Tile* two = nullptr;
	Tile* three = nullptr;
	Tile* four = nullptr;
	Tile* five = nullptr;
	Tile* six = nullptr;
	Tile* seven = nullptr;
	Tile* eight = nullptr;
	sf::Vector2f data1;
	sf::Vector2f data2;
	sf::Vector2f data3;
	sf::Vector2f data4;
	sf::Vector2f data5;
	sf::Vector2f data6;
	sf::Vector2f data7;
	sf::Vector2f data8;
	//};



	Tile(int xPos = 0, int yPos = 0);
	void Update(vector<Tile>& tile, vector<Tile*>& adjacentTiles);
	Tile* current = nullptr;
	void SetHidden(bool I)
	{
		isHidden = I;
	}
	void SetRevealedTile(bool I)
	{
		revealTile = I;
	}
	void SetMines(bool I)
	{
		isMine = I;
	}
	void SetFlag(bool I)
	{
		hasFlag = I;
	}
	void ResetTile(bool I)
	{
		resetTile = I;
	}
	void SetDebug(bool I)
	{
		debug = I;
	}
	void SetOnes(bool I, int place)
	{
		Ones = I;
		onesposition = place;
	}
	void SetTens(bool I, int place)
	{
		Tens = I;
		tensposition = place;
	}
	void SetHundreds(bool I, int place)
	{
		Hundreds = I;
		hundredsposition = place;
	}
	void SetThousands(bool I, bool negative)
	{
		Thousands = I;
		Negative = negative;
	}
	void SetTest1(bool I)
	{
		test1 = I;
	}
	void SetTest2(bool I)
	{
		test2 = I;
	}
	void SetTest3(bool I)
	{
		test3 = I;
	}
	void SetVictory(bool I)
	{
		victory = I;
	}
	void SetDefeat(bool I)
	{
		defeat = I;
	}
	void SetNumberOne(bool I, int J)
	{
		numberone = I;
		number = J;
	}


};