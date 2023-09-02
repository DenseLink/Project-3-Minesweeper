#include "Tile.h"
//#include "revealedTile.h"
#include "TextureManager.h"
//#include "Project 3 Minesweeper.cpp"
//#include "hiddenTile.h"
#include <iostream>

using namespace std;
Tile::Tile(int xPos, int yPos)
{
	setPosition(xPos, yPos);
	//setTexture(TextureManager::GetTexture("tile_hidden"));
	auto rect = getTextureRect();
}

void Tile::Update(vector<Tile>& tile, vector<Tile*>& adjacentTiles)
{
	//	rotate(rotationRate);
	for (unsigned int i = 0; i < tile.size(); i++)
	{
		Tile* nTile = new Tile;
		//if tile is a corner
		if (i < 400)//(i == 0 || 24 || 374 || 399)
		{
			if (i == 0)
			{
				nTile->one = &tile[1];
				nTile->data1 = nTile->one->getPosition();
				nTile->two = &tile[25];
				nTile->data2 = tile[25].getPosition();
				nTile->three = &tile[26];
				nTile->data3 = tile[26].getPosition();
				//nTile->data1 = nTile->one.getPosition()
			}
			else if (i == 24)
			{
				nTile->one = &tile[23];
				nTile->two = &tile[48];
				nTile->three = &tile[49];
				nTile->data1 = tile[23].getPosition();
				nTile->data2 = tile[48].getPosition();
				nTile->data3 = tile[49].getPosition();
			}
			else if (i == 375)
			{
				nTile->one = &tile[350];
				nTile->two = &tile[376];
				nTile->three = &tile[351];
				nTile->data1 = tile[350].getPosition();
				nTile->data2 = tile[376].getPosition();
				nTile->data3 = tile[351].getPosition();
				//nTile->data4 = tile[374].getPosition();
			}
			else if (i == 399)
			{
				nTile->one = &tile[398];
				nTile->two = &tile[374];
				nTile->three = &tile[373];
				nTile->data1 = tile[398].getPosition();
				nTile->data2 = tile[374].getPosition();
				nTile->data3 = tile[373].getPosition();
			}
			//}
			//if tile is a side piece
			//else //if (i % 25 == 0 || /*left side*/ i % 24 == 0 /*right side*/ || i < 25 /*top side*/ || (i > 374 && i < 400) /*bottom side*/)
			//{
			else if (i < 24)
			{
				nTile->one = &tile[(i + 1)];
				nTile->two = &tile[(i - 1)];
				nTile->three = &tile[(i + 25)];
				nTile->four = &tile[(i + 24)];
				nTile->five = &tile[(i + 26)];
				nTile->data1 = tile[(i + 1)].getPosition();
				nTile->data2 = tile[(i - 1)].getPosition();
				nTile->data3 = tile[(i + 25)].getPosition();
				nTile->data4 = tile[(i + 24)].getPosition();
				nTile->data5 = tile[(i + 26)].getPosition();
			}
			else if (i > 375 && i < 400)
			{
				nTile->one = &tile[(i + 1)];
				nTile->two = &tile[(i - 1)];
				nTile->three = &tile[(i - 25)];
				nTile->four = &tile[(i - 26)];
				nTile->five = &tile[(i - 24)];
				nTile->data1 = tile[(i + 1)].getPosition();
				nTile->data2 = tile[(i - 1)].getPosition();
				nTile->data3 = tile[(i - 25)].getPosition();
				nTile->data4 = tile[(i - 26)].getPosition();
				nTile->data5 = tile[(i - 24)].getPosition();
			}
			else if (i % 25 == 0 && i != 375)
			{
				nTile->one = &tile[(i - 25)];
				nTile->two = &tile[(i + 25)];
				nTile->three = &tile[(i - 24)];
				nTile->four = &tile[(i + 26)];
				nTile->five = &tile[(i + 1)];
				nTile->data1 = tile[(i - 25)].getPosition();
				nTile->data2 = tile[(i + 25)].getPosition();
				nTile->data3 = tile[(i - 24)].getPosition();
				nTile->data4 = tile[(i + 26)].getPosition();
				nTile->data5 = tile[(i + 1)].getPosition();
			}
			else if (i == 49 || i == 74 || i == 99 || i == 124 || i == 149 || i == 174 || i == 199 || i == 224 || i == 249 || i == 274 || i == 299 || i == 324 || i == 349 || i == 374)
			{
				nTile->one = &tile[(i - 25)];
				nTile->two = &tile[(i + 25)];
				nTile->three = &tile[(i - 26)];
				nTile->four = &tile[(i + 24)];
				nTile->five = &tile[(i - 1)];
				nTile->data1 = tile[(i - 25)].getPosition();
				nTile->data2 = tile[(i + 25)].getPosition();
				nTile->data3 = tile[(i - 26)].getPosition();
				nTile->data4 = tile[(i + 24)].getPosition();
				nTile->data5 = tile[(i - 1)].getPosition();
			}
			// if tile is a middle piece
			else
			{
				nTile->one = &tile[(i - 25)];
				nTile->two = &tile[(i + 25)];
				nTile->three = &tile[(i - 26)];
				nTile->four = &tile[(i + 24)];
				nTile->five = &tile[(i - 1)];
				nTile->six = &tile[(i - 24)];
				nTile->seven = &tile[(i + 26)];
				nTile->eight = &tile[(i + 1)];
				nTile->data1 = tile[(i - 25)].getPosition();
				nTile->data2 = tile[(i + 25)].getPosition();
				nTile->data3 = tile[(i - 26)].getPosition();
				nTile->data4 = tile[(i + 24)].getPosition();
				nTile->data5 = tile[(i - 1)].getPosition();
				nTile->data6 = tile[(i - 24)].getPosition();
				nTile->data7 = tile[(i + 26)].getPosition();
				nTile->data8 = tile[(i + 1)].getPosition();
			}
			//tile[i].Update();
		}
		adjacentTiles.push_back(nTile);
	}
}
