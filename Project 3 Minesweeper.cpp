#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"

#include "Tile.h"
#include "random"
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <sstream>

//extern bool isHidden;
using namespace std;
mt19937 random_mt(time(0));

int reductionx(int& x);
int reductiony(int& y);
void recursiontiles(int& xposition, int& yposition, vector<Tile>& rev_mine, vector<Tile>& tile, vector<Tile*>& adjacentTiles, vector<Tile>& rev_tile, int& recursioncounter, vector<Tile>& flag);
void check(int& xposition, int& yposition, vector<Tile>& rev_mine, vector<Tile>& rev_tile, bool& value, bool& value2, bool& revTest, bool& adjacent_mines_or_revealed_tiles, bool& rev_adjacentTiles, vector<Tile>& flag);
void test(string& path, vector<Tile>& rev_tile, vector<Tile>& rev_mine, vector<Tile*>& adjacentTiles, vector<Tile>& flag, vector<Tile>& sec_mine, vector<Tile>& tile, int& COUNTER);
void moremines(vector<Tile>& rev_mine);
void Draw_Numbers(int& xposition, int& yposition, vector<Tile>& tile, vector<Tile>& rev_tile, vector<Tile>& rev_mine, vector<Tile*>& adjacentTiles, vector<Tile>& number, vector<int>& num1);
int Random(int min, int max)
{
	//std::mt19937 random_mt(time(0));
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}
int main()
{
	int recursioncounter = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	//sf::RenderWindow window.setPosition(0, 0);
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Blue);													//Goodbye my blue friend


	/*=========================INITIALIZATION==========================================*/
	//2. Set a Sprite's tecture to that which is loaded:L
	sf::Sprite background;

	const int width = 25;
	const int height = 16;
	vector<Tile> tile; //test
	//vector<hiddenTile> tile;
	vector<Tile> rev_tile;
	vector<Tile> rev_mine;
	vector<Tile> sec_mine;
	vector<Tile*> adjacentTiles;
	vector<Tile> flag;
	vector<Tile> debugtile;
	vector<Tile> ones;
	vector<Tile> tens;
	vector<Tile> hundreds;
	vector<Tile> thousands;
	vector<Tile> test1;
	vector<Tile> test2;
	vector<Tile> test3;
	vector<Tile> victory;
	vector<Tile> defeat;
	vector<Tile> number;
	vector<int> num1;

	//vector<Tile> temp_flag;
	vector<Tile> reset;
	int temp_counter = 0;
	for (int i = 0; i < height * 32; i += 32)
	{
		for (int j = 0; j < width * 32; j += 32)
		{
			tile.push_back(Tile(j, i));
		}
	}
	//COUNTER = rev_mine.size();
	for (int i = 0; i < 50; i++)
	{
		int horizontal_position = Random(0, ((width - 1) * 32));
		horizontal_position = reductionx(horizontal_position);
		//rev_tile.push_back(revealedTile(i,j));

		int vertical_position = Random(0, ((height - 1) * 32));
		vertical_position = reductiony(vertical_position);

		rev_mine.push_back(Tile(horizontal_position, vertical_position));
	}
	moremines(rev_mine);
	//pointer vector
	//for (int i = 0; i < tile.size(); i++)
	//{
	Tile getPointers;
	getPointers.Update(tile, adjacentTiles);
	//}
	//reset button
	for (int i = 0; i < 1; i++)
	{
		int horizontal_position = (width - 6) * 32;
		int vertical_position = (height) * 32;
		reset.push_back(Tile(horizontal_position, vertical_position));
	}
	//for debug
	for (int i = 0; i < 1; i++)
	{
		int horizontal_position = (width - 4) * 32;
		int vertical_position = (height) * 32;
		debugtile.push_back(Tile(horizontal_position, vertical_position));
	}
	//thousands position on counter
	for (int i = 0; i < 1; i++)
	{
		int horizontal_position = 0;
		int vertical_position = (height) * 32;
		thousands.push_back(Tile(horizontal_position, vertical_position));
	}
	for (int i = 0; i < 1; i++)//hundreds position on counter
	{
		int horizontal_position = 32;
		int vertical_position = (height) * 32;
		hundreds.push_back(Tile(horizontal_position, vertical_position));
	}
	for (int i = 0; i < 1; i++)//tens position on counter
	{
		int horizontal_position = 64;
		int vertical_position = (height) * 32;
		tens.push_back(Tile(horizontal_position, vertical_position));
	}
	for (int i = 0; i < 1; i++)//ones position on counter
	{
		int horizontal_position = 96;
		int vertical_position = (height) * 32;
		ones.push_back(Tile(horizontal_position, vertical_position));
	}
	for (int i = 0; i < 1; i++)//test 1
	{
		int horizontal_position = 7 * 32;
		int vertical_position = (height) * 32;
		test1.push_back(Tile(horizontal_position, vertical_position));
	}
	for (int i = 0; i < 1; i++)//test 2
	{
		int horizontal_position = 9 * 32;
		int vertical_position = (height) * 32;
		test2.push_back(Tile(horizontal_position, vertical_position));
	}
	for (int i = 0; i < 1; i++)//test 3
	{
		int horizontal_position = 11 * 32;
		int vertical_position = (height) * 32;
		test3.push_back(Tile(horizontal_position, vertical_position));
	}
	//background.setTexture(TextureManager::GetTexture("digits", sf::IntRect(0,21,32,32));
	int COUNTER = rev_mine.size();
	int number_till_victory;
	bool revealAllMines = true;
	bool revealedMine = false;
	bool victoryCondition = false;
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				auto mousePos = sf::Mouse::getPosition(window);
				//shape.setPosition(mousePos.x, mousePos.y);									//goodbye my friend
				//if I left click
				if ((event.mouseButton.button == sf::Mouse::Left) && revealedMine == false)
				{
					//REVEALING THE TILES
					//1. Get the mouse position
					//auto mousePos = sf::Mouse::getPosition(window);
					//shape.setPosition(mousePos.x, mousePos.y);
					if (mousePos.y > 0 && mousePos.y < height * 32 && mousePos.x > 0 && mousePos.x < width * 32)
					{
						int horizontalPosition = reductionx(mousePos.x);

						int verticalPosition = mousePos.y / 32;//reductiony(mousePos.y); 
						verticalPosition *= 32;
						//reveal the tiles after clicking on them

						if (flag.size() == 0)
						{
							bool was_mine_selected = false;
							if (was_mine_selected == false)
							{
								for (int i = 0; i < rev_mine.size(); i++)
								{
									auto a = rev_mine[i].getPosition();
									int h = a.x;
									int v = a.y;
									//REVEAL MINE IF A TILE WITH A MINE UNDERNEATH IS CLICKED ON
									if (horizontalPosition == h && verticalPosition == v)
									{
										//sec_mine.push_back(rev_mine[i]);
										for (int i = 0; i < rev_mine.size(); i++)
										{
											sec_mine.push_back(rev_mine[i]);
										}
										revealedMine = true;
										int defeatx = (width - 6) * 32;
										int defeaty = (height) * 32;
										defeat.push_back(Tile(defeatx, defeaty));
										was_mine_selected = true;
									}
								}

							}
							if (was_mine_selected == false)
							{
								recursiontiles(horizontalPosition, verticalPosition, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag);
							}
							//rev_tile.push_back(Tile(horizontalPosition, verticalPosition));						//I AM COMMENTING OUT THIS LINE TO WORK ON RECURSION
							//write the victory condition
							number_till_victory = 0;
							bool noduplication = true;
							for (int i = 0; i < tile.size(); i++)
							{
								noduplication = true;
								auto a = tile[i].getPosition();
								int h = a.x;

								int v = a.y;
								for (int j = 0; j < rev_tile.size(); j++)
								{
									auto aa = rev_tile[j].getPosition();
									int hh = aa.x;
									int vv = aa.y;
									if (h == hh && v == vv && noduplication == true)
									{
										noduplication = false;
										number_till_victory++;
									}
								}
							}

							if (number_till_victory + rev_mine.size() == 400)
							{
								victoryCondition = true;
								flag.erase(flag.begin(), flag.begin() + flag.size());

								for (int i = 0; i < rev_mine.size(); i++)
								{
									flag.push_back(rev_mine[i]);
								}
								int victoryx = (width - 6) * 32;
								int victoryy = (height) * 32;
								victory.push_back(Tile(victoryx, victoryy));
								COUNTER = 0;
							}

							for (int i = 0; i < rev_mine.size(); i++)
							{
								auto a = rev_mine[i].getPosition();
								int h = a.x;
								int v = a.y;
								//REVEAL MINE IF A TILE WITH A MINE UNDERNEATH IS CLICKED ON
								if (horizontalPosition == h && verticalPosition == v)
								{
									//sec_mine.push_back(rev_mine[i]);
									for (int i = 0; i < rev_mine.size(); i++)
									{
										sec_mine.push_back(rev_mine[i]);
									}
									revealedMine = true;
									int defeatx = (width - 6) * 32;
									int defeaty = (height) * 32;
									defeat.push_back(Tile(defeatx, defeaty));

								}
							}
							//IF THIS DOESN"T WORK PLACE CODE BACK HERE
						}
						else {
							int flagstop = -1;
							int flagstop1 = -1;
							for (int j = 0; j < flag.size(); j++)
							{
								auto clickedTile = flag[j].getPosition();
								int clickedTilex = clickedTile.x;
								int clickedTiley = clickedTile.y;
								if (clickedTilex == horizontalPosition && clickedTiley == verticalPosition)
								{
									flagstop = horizontalPosition;
									flagstop1 = verticalPosition;
								}
							}
							if (flagstop != horizontalPosition && flagstop1 != verticalPosition)
							{
								bool was_mine_selected = false;
								if (was_mine_selected == false)
								{
									for (int i = 0; i < rev_mine.size(); i++)
									{
										auto a = rev_mine[i].getPosition();
										int h = a.x;
										int v = a.y;
										//REVEAL MINE IF A TILE WITH A MINE UNDERNEATH IS CLICKED ON
										if (horizontalPosition == h && verticalPosition == v)
										{
											//sec_mine.push_back(rev_mine[i]);
											for (int i = 0; i < rev_mine.size(); i++)
											{
												sec_mine.push_back(rev_mine[i]);
											}
											revealedMine = true;
											int defeatx = (width - 6) * 32;
											int defeaty = (height) * 32;
											defeat.push_back(Tile(defeatx, defeaty));
											was_mine_selected = true;
										}
									}
								}
								if (was_mine_selected == false)
								{
									recursiontiles(horizontalPosition, verticalPosition, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag);
								}
								//rev_tile.push_back(Tile(horizontalPosition, verticalPosition));						//I AM COMMMENTING OUT THIS LINE TO WORK ON RECURSION
								//write the victory condition
								number_till_victory = 0;
								bool noduplication = true;
								for (int i = 0; i < tile.size(); i++)
								{
									noduplication = true;
									auto a = tile[i].getPosition();
									int h = a.x;

									int v = a.y;
									for (int j = 0; j < rev_tile.size(); j++)
									{
										auto aa = rev_tile[j].getPosition();
										int hh = aa.x;
										int vv = aa.y;
										if (h == hh && v == vv && noduplication == true)
										{
											noduplication = false;
											number_till_victory++;
										}
									}
								}

								if (number_till_victory + rev_mine.size() == 400)
								{
									victoryCondition = true;
									flag.erase(flag.begin(), flag.begin() + flag.size());

									for (int i = 0; i < rev_mine.size(); i++)
									{
										flag.push_back(rev_mine[i]);
									}
									int victoryx = (width - 6) * 32;
									int victoryy = (height) * 32;
									victory.push_back(Tile(victoryx, victoryy));
									COUNTER = 0;
								}


								for (int i = 0; i < rev_mine.size(); i++)
								{
									auto a = rev_mine[i].getPosition();
									int h = a.x;
									int v = a.y;
									//REVEAL MINE IF A TILE WITH A MINE UNDERNEATH IS CLICKED ON
									if (horizontalPosition == h && verticalPosition == v)
									{
										//sec_mine.push_back(rev_mine[i]);
										for (int i = 0; i < rev_mine.size(); i++)
										{
											sec_mine.push_back(rev_mine[i]);
										}
										revealedMine = true;
										int defeatx = (width - 6) * 32;
										int defeaty = (height) * 32;
										defeat.push_back(Tile(defeatx, defeaty));
									}
								}
							}
						}
						//recursiontiles(horizontalPosition, verticalPosition, rev_mine, tile, adjacentTiles, rev_tile);				//I AM COMMENTING THIS OUT TO PLACE INSIDE WIN AND LOSE CONDITIONS


						//reveal the mines after clicking on them
						//for (int i = 0; i < rev_mine.size(); i++)
						//{
						//	auto a = rev_mine[i].getPosition();
						//	int h = a.x;
						//	int v = a.y;
						//	//REVEAL MINE IF A TILE WITH A MINE UNDERNEATH IS CLICKED ON
						//	if (horizontalPosition == h && verticalPosition == v)
						//	{
						//		sec_mine.push_back(rev_mine[i]);
						//	}
							//REVEAL ADJACENT TILES IF THERE ARE NO MINES NEARBY
							//else if (horizontalPosition != h && verticalPosition != v) //if the clicked mouseposition isn't a mine tile
							//{
							//	recursiontiles(horizontalPosition, verticalPosition, rev_mine, tile, adjacentTiles, rev_tile);
							//}
						//}
					}
				}
				//if I right click
				if ((event.mouseButton.button == sf::Mouse::Right) && revealedMine == false)
				{
					//auto mousePos = sf::Mouse::getPosition(window);
					//shape.setPosition(mousePos.x, mousePos.y);
					if (mousePos.y > 0 && mousePos.y < height * 32 && mousePos.x > 0 && mousePos.x < width * 32)
					{
						int horizontalPosition = reductionx(mousePos.x);

						int verticalPosition = mousePos.y / 32;
						verticalPosition *= 32;
						if (flag.size() == 0)
						{
							flag.push_back(Tile(horizontalPosition, verticalPosition));
							COUNTER--;
						}
						else {
							bool allow = true;
							bool secondCheck = true;
							int check = -1;
							int check2 = -1;
							int flagint = 0;
							int finalFlagCount = 0;
							for (flagint; flagint < flag.size(); flagint++)
							{
								auto clickedTile = flag[flagint].getPosition();
								int clickedTilex = clickedTile.x;
								int clickedTiley = clickedTile.y;
								if (clickedTilex == horizontalPosition && clickedTiley == verticalPosition)
								{
									check = clickedTilex;
									check2 = clickedTiley;
									finalFlagCount = flagint;
								}
							}
							for (int i = 0; i < flag.size(); i++)
							{
								auto clickedTile = flag[i].getPosition();
								int clickedTilex = clickedTile.x;
								int clickedTiley = clickedTile.y;
								//auto newestTile = flag
								if ((check == horizontalPosition && check2 == verticalPosition) && secondCheck == true)
								{

									flag.erase(flag.begin() + finalFlagCount);
									secondCheck = false;
									allow = false;
									COUNTER++;
								}
								else if ((clickedTilex == horizontalPosition && clickedTiley == verticalPosition) /*|| (check == horizontalPosition || check2 == verticalPosition)*/ && secondCheck == true)
								{
									flag.erase(flag.begin() + i);
									secondCheck == false;
									COUNTER++;
								}
								else if ((clickedTilex != horizontalPosition || clickedTiley != verticalPosition) && allow == true)
								{
									flag.push_back(Tile(horizontalPosition, verticalPosition));
									allow = false;
									secondCheck = false;
									COUNTER--;
								}

							}
							//allow = true;
							//secondCheck = true;
						}


					}
				}
				//if I click the reset button
				if (mousePos.y > (height * 32) && mousePos.y < (height * 32 + 64) && mousePos.x >((width - 6) * 32) && mousePos.x < ((width - 6) * 32 + 64))
				{
					revealedMine = false;
					revealAllMines = true;
					mt19937 random_mt(time(0));
					rev_tile.erase(rev_tile.begin(), rev_tile.begin() + rev_tile.size());
					rev_mine.erase(rev_mine.begin(), rev_mine.begin() + rev_mine.size());
					adjacentTiles.erase(adjacentTiles.begin(), adjacentTiles.begin() + rev_tile.size());
					flag.erase(flag.begin(), flag.begin() + flag.size());
					sec_mine.erase(sec_mine.begin(), sec_mine.begin() + sec_mine.size());
					defeat.erase(defeat.begin(), defeat.begin() + defeat.size());
					number.erase(number.begin(), number.begin() + number.size());
					num1.erase(num1.begin(), num1.begin() + num1.size());
					for (int i = 0; i < 50; i++)
					{
						int horizontal_position = Random(0, ((width - 1) * 32));
						horizontal_position = reductionx(horizontal_position);
						//rev_tile.push_back(revealedTile(i,j));

						int vertical_position = Random(0, ((height - 1) * 32));
						vertical_position = reductiony(vertical_position);

						rev_mine.push_back(Tile(horizontal_position, vertical_position));
					}
					moremines(rev_mine);
					//for (int i = 0; i < tile.size(); i++)
					//{
					Tile getPointers;
					getPointers.Update(tile, adjacentTiles);
					//}
					COUNTER = rev_mine.size();
					victory.erase(victory.begin(), victory.begin() + victory.size());
				}
				//If I click the debugger
				if ((mousePos.y > (height * 32) && mousePos.y < (height * 32 + 64) && mousePos.x >((width - 4) * 32) && mousePos.x < ((width - 4) * 32 + 64)) && revealedMine == false)
				{

					if (revealAllMines == true)
					{
						for (int i = 0; i < rev_mine.size(); i++)
						{
							sec_mine.push_back(rev_mine[i]);
						}
						revealAllMines = false;
					}
					else if (revealAllMines == false)
					{
						sec_mine.erase(sec_mine.begin(), sec_mine.begin() + sec_mine.size());
						revealAllMines = true;
					}
				}
				//if I click test 1
				if ((mousePos.y > (height * 32) && mousePos.y < (height * 32 + 64) && mousePos.x >(7 * 32) && mousePos.x < ((7) * 32 + 64)) && revealedMine == false)
				{
					number.erase(number.begin(), number.begin() + number.size());
					num1.erase(num1.begin(), num1.begin() + num1.size());
					victory.erase(victory.begin(), victory.begin() + victory.size());
					defeat.erase(defeat.begin(), defeat.begin() + defeat.size());
					revealAllMines = true;
					string s = "/boards/testBoard1.brd";
					test(s, rev_tile, rev_mine, adjacentTiles, flag, sec_mine, tile, COUNTER);

				}
				//if I click test 2
				if ((mousePos.y > (height * 32) && mousePos.y < (height * 32 + 64) && mousePos.x >(9 * 32) && mousePos.x < ((9) * 32 + 64)) && revealedMine == false)
				{
					number.erase(number.begin(), number.begin() + number.size());
					num1.erase(num1.begin(), num1.begin() + num1.size());
					victory.erase(victory.begin(), victory.begin() + victory.size());
					defeat.erase(defeat.begin(), defeat.begin() + defeat.size());
					revealAllMines = true;
					string s = "/boards/testBoard2.brd";
					test(s, rev_tile, rev_mine, adjacentTiles, flag, sec_mine, tile, COUNTER);
				}
				//if I click test 3
				if ((mousePos.y > (height * 32) && mousePos.y < (height * 32 + 64) && mousePos.x >((11) * 32) && mousePos.x < (11 * 32 + 64)) && revealedMine == false)
				{
					victory.erase(victory.begin(), victory.begin() + victory.size());
					defeat.erase(defeat.begin(), defeat.begin() + defeat.size());
					number.erase(number.begin(), number.begin() + number.size());
					num1.erase(num1.begin(), num1.begin() + num1.size());
					revealAllMines = true;
					string s = "/boards/testBoard3.brd";
					test(s, rev_tile, rev_mine, adjacentTiles, flag, sec_mine, tile, COUNTER);
				}
			}
			//else if(event.type == sf::Event::M)
		}
		window.clear();

		//draw the background
		window.draw(background);
		//draw the other sprites
		//window.draw(shape);													//goodbye friend
		//draw all the revealed tiles

		//draw all the hidden tiles over the revealed tiles
		//for (int i = 0; i < tile.size(); i++)
		//{
		//	window.draw(tile[i]);
		//}
		//THIS CODE DRAWS THE HIDDEN TILES
		for (int i = 0; i < tile.size(); i++)
		{

			Tile setHiddentTile;
			setHiddentTile.SetHidden(true);
			auto tilePos = tile[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setHiddentTile.Draw(window, tilex, tiley);
			setHiddentTile.SetHidden(false);
		}

		for (int i = 0; i < rev_tile.size(); i++)
		{
			Tile setRevealedTile;
			setRevealedTile.SetRevealedTile(true);
			//window.draw(rev_tile[i]);
			auto tilePos = rev_tile[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setRevealedTile.Draw(window, tilex, tiley);
			setRevealedTile.SetRevealedTile(false);
		}
		for (int i = 0; i < sec_mine.size(); i++)
		{
			Tile DrawMines;
			DrawMines.SetMines(true);
			auto tilePos = sec_mine[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			DrawMines.Draw(window, tilex, tiley);
			DrawMines.SetMines(false);

		}
		for (int i = 0; i < flag.size(); i++)
		{
			Tile setFlag;
			setFlag.SetFlag(true);
			//window.draw(rev_tile[i]);
			auto tilePos = flag[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setFlag.Draw(window, tilex, tiley);
			setFlag.SetFlag(false);
		}
		for (int i = 0; i < reset.size(); i++)
		{
			Tile setReset;
			setReset.ResetTile(true);
			auto tilePos = reset[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setReset.Draw(window, tilex, tiley);
			setReset.ResetTile(false);
		}
		for (int i = 0; i < debugtile.size(); i++)
		{
			Tile setDebug;
			setDebug.SetDebug(true);
			auto tilePos = debugtile[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setDebug.Draw(window, tilex, tiley);
			setDebug.ResetTile(false);
		}
		for (int i = 0; i < thousands.size(); i++) //Second gate is if count is negative
		{
			if (COUNTER < 0)
			{
				Tile setThousands;
				setThousands.SetThousands(true, true);//Second gate is if count is negative
				auto tilePos = thousands[i].getPosition();
				int tilex = tilePos.x;
				int tiley = tilePos.y;
				setThousands.Draw(window, tilex, tiley);
				setThousands.SetThousands(false, false);//Second gate is if count is negative
			}
			else {
				Tile setThousands;
				setThousands.SetThousands(true, false);//Second gate is if count is negative
				auto tilePos = thousands[i].getPosition();
				int tilex = tilePos.x;
				int tiley = tilePos.y;
				setThousands.Draw(window, tilex, tiley);
				setThousands.SetThousands(false, false);//Second gate is if count is negative

			}
		}
		for (int i = 0; i < hundreds.size(); i++)
		{
			if (COUNTER > (-351)) {
				int temp = COUNTER / 100;
				int hundredsposition = (temp % 10);
				Tile setHundreds;
				setHundreds.SetHundreds(true, hundredsposition); //Second gate is if count is negative
				auto tilePos = hundreds[i].getPosition();
				int tilex = tilePos.x;
				int tiley = tilePos.y;
				setHundreds.Draw(window, tilex, tiley);
				setHundreds.SetHundreds(false, hundredsposition);
			}
		}
		for (int i = 0; i < tens.size(); i++)
		{
			if (COUNTER > (-351))
			{
				int temp = COUNTER / 10;
				int tensposition = (temp % 10);
				Tile setTens;
				setTens.SetTens(true, tensposition);
				auto tilePos = tens[i].getPosition();
				int tilex = tilePos.x;
				int tiley = tilePos.y;
				setTens.Draw(window, tilex, tiley);
				setTens.SetTens(false, tensposition);
			}
		}
		for (int i = 0; i < ones.size(); i++)
		{
			if (COUNTER > (-351)) {
				int onesposition = (COUNTER % 10);
				Tile setOnes;
				setOnes.SetOnes(true, onesposition);//Second gate is the number of % mod
				auto tilePos = ones[i].getPosition();
				int tilex = tilePos.x;
				int tiley = tilePos.y;
				setOnes.Draw(window, tilex, tiley);
				setOnes.SetOnes(false, onesposition);//Second gate is the number of % mod
			}
		}
		for (int i = 0; i < test1.size(); i++)
		{
			Tile setTest1;
			setTest1.SetTest1(true);
			auto tilePos = test1[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setTest1.Draw(window, tilex, tiley);
			setTest1.SetTest1(false);
		}
		for (int i = 0; i < test2.size(); i++)
		{
			Tile setTest2;
			setTest2.SetTest2(true);
			auto tilePos = test2[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setTest2.Draw(window, tilex, tiley);
			setTest2.SetTest2(false);
		}
		for (int i = 0; i < test3.size(); i++)
		{
			Tile setTest3;
			setTest3.SetTest3(true);
			auto tilePos = test3[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setTest3.Draw(window, tilex, tiley);
			setTest3.SetTest3(false);
		}
		for (int i = 0; i < defeat.size(); i++)
		{
			Tile setDefeat;
			setDefeat.SetDefeat(true);
			auto tilePos = defeat[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setDefeat.Draw(window, tilex, tiley);
			setDefeat.SetDefeat(false);
		}
		for (int i = 0; i < victory.size(); i++)
		{
			Tile setVictory;
			setVictory.SetVictory(true);
			auto tilePos = victory[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			setVictory.Draw(window, tilex, tiley);
			setVictory.SetVictory(false);
		}

		for (int i = 0; i < rev_tile.size(); i++)
		{
			auto a = rev_tile[i].getPosition();
			int h = a.x;
			int v = a.y;
			Draw_Numbers(h, v, tile, rev_tile, rev_mine, adjacentTiles, number, num1);
		}
		for (int i = 0; i < number.size(); i++)
		{
			Tile drawNumber;
			drawNumber.SetNumberOne(true, num1[i]);

			auto tilePos = number[i].getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;
			drawNumber.Draw(window, tilex, tiley);
			drawNumber.SetNumberOne(false, num1[i]);
		}



		window.display();
		//adjacent tiles
		for (int i = 0; i < 1; i++)
		{
			auto tilePos = adjacentTiles[i]->data1;
			//	auto tilePos = adjacentTiles[i]->one->getPosition();
			int tilex = tilePos.x;
			int tiley = tilePos.y;

		}
	}
	//==========Shutdown/Cleanup=================
	TextureManager::Clear();
	return 0;
}
int reductionx(int& x)
{
	if (x % 32 == 0)
	{
		return x;
	}
	else
	{
		--x;
		reductionx(x);
	}
}
int reductiony(int& y)
{
	if (y % 32 == 0)
	{
		return y;
	}
	else
	{
		--y;
		reductionx(y);
	}
}
void recursiontiles(int& xposition, int& yposition, vector<Tile>& rev_mine, vector<Tile>& tile, vector<Tile*>& adjacentTiles, vector<Tile>& rev_tile, int& recursioncounter, vector<Tile>& flag)
{
	/*recursioncounter++;
	if (recursioncounter == 371)
	{
		int sdfs = 0;
	}*/
	//set gates equal to true
	bool first = false;
	bool second = false;
	bool third = false;
	bool fourth = false;
	bool fifth = false;
	bool sixth = false;
	bool seventh = false;
	bool eighth = false;
	bool aa = false;
	bool bb = false;
	bool cc = false;
	bool dd = false;
	bool ee = false;
	bool ff = false;
	bool gg = false;
	bool hh = false;

	bool adjacent_mines_or_revealed_tiles1 = false;
	bool adjacent_mines_or_revealed_tiles2 = false;
	bool adjacent_mines_or_revealed_tiles3 = false;
	bool adjacent_mines_or_revealed_tiles4 = false;
	bool adjacent_mines_or_revealed_tiles5 = false;
	bool adjacent_mines_or_revealed_tiles6 = false;
	bool adjacent_mines_or_revealed_tiles7 = false;
	bool adjacent_mines_or_revealed_tiles8 = false;

	bool revtile1 = false;
	bool revtile2 = false;
	bool revtile3 = false;
	bool revtile4 = false;
	bool revtile5 = false;
	bool revtile6 = false;
	bool revtile7 = false;
	bool revtile8 = false;
	int j;
	//find tile position of the coordinates passed in
	for (int uz = 0; uz < tile.size(); uz++)
	{
		auto uniquea = tile[uz].getPosition();
		int uniqueh = uniquea.x;
		int uniquev = uniquea.y;
		if (xposition == uniqueh && yposition == uniquev)
		{
			j = uz;
		}
	}
	//if the tile that I am currently at has not already been revealed
	bool revTest = true;
	for (int j = 0; j < rev_tile.size(); j++)
	{
		auto clickedTile = rev_tile[j].getPosition();
		int clickedTilex = clickedTile.x;
		int clickedTiley = clickedTile.y;
		if (clickedTilex == xposition && clickedTiley == yposition)
		{
			revTest = false;
		}
	}

	//for (int j = 0; j < rev_tile.size(); j++)
	//{
	//	auto clickedTile = rev_tile[j].getPosition();
	//	int clickedTilex = clickedTile.x;
	//	int clickedTiley = clickedTile.y;
	//	if (clickedTilex == xposition && clickedTiley == yposition)
	//	{
	//		revTest = false;
	//	}
	//}
	//Get x y coordinates of starting tile
	auto clickedTile = tile[j].getPosition();
	int clickedTilex = clickedTile.x;
	int clickedTiley = clickedTile.y;
	//Get x y coordinates of adjacent tiles
	auto tilePos1 = adjacentTiles[j]->data1;
	int tilePos1x = tilePos1.x;
	int tilePos1y = tilePos1.y;

	auto tilePos2 = adjacentTiles[j]->data2;
	int tilePos2x = tilePos2.x;
	int tilePos2y = tilePos2.y;

	auto tilePos3 = adjacentTiles[j]->data3;
	int tilePos3x = tilePos3.x;
	int tilePos3y = tilePos3.y;

	auto tilePos4 = adjacentTiles[j]->data4;
	int tilePos4x = tilePos4.x;
	int tilePos4y = tilePos4.y;

	auto tilePos5 = adjacentTiles[j]->data5;
	int tilePos5x = tilePos5.x;
	int tilePos5y = tilePos5.y;

	auto tilePos6 = adjacentTiles[j]->data6;
	int tilePos6x = tilePos6.x;
	int tilePos6y = tilePos6.y;

	auto tilePos7 = adjacentTiles[j]->data7;
	int tilePos7x = tilePos7.x;
	int tilePos7y = tilePos7.y;

	auto tilePos8 = adjacentTiles[j]->data8;
	int tilePos8x = tilePos8.x;
	int tilePos8y = tilePos8.y;

	check(tilePos1x, tilePos1y, rev_mine, rev_tile, first, aa, revTest, adjacent_mines_or_revealed_tiles1, revtile1, flag);
	check(tilePos2x, tilePos2y, rev_mine, rev_tile, second, bb, revTest, adjacent_mines_or_revealed_tiles2, revtile2, flag);
	check(tilePos3x, tilePos3y, rev_mine, rev_tile, third, cc, revTest, adjacent_mines_or_revealed_tiles3, revtile3, flag);
	check(tilePos4x, tilePos4y, rev_mine, rev_tile, fourth, dd, revTest, adjacent_mines_or_revealed_tiles4, revtile4, flag);
	check(tilePos5x, tilePos5y, rev_mine, rev_tile, fifth, ee, revTest, adjacent_mines_or_revealed_tiles5, revtile5, flag);
	check(tilePos6x, tilePos6y, rev_mine, rev_tile, sixth, ff, revTest, adjacent_mines_or_revealed_tiles6, revtile6, flag);
	check(tilePos7x, tilePos7y, rev_mine, rev_tile, seventh, gg, revTest, adjacent_mines_or_revealed_tiles7, revtile7, flag);
	check(tilePos8x, tilePos8y, rev_mine, rev_tile, eighth, hh, revTest, adjacent_mines_or_revealed_tiles8, revtile8, flag);
	//if(first|| second || third || fourth || fifth || sixth || seventh || eighth || aa || bb || cc || dd || ee || ff || gg || hh == false)
	//{
	int z = 0;
	//}
	//else {
		//Set coordinates of mines if they are adjacent to my square
	int h1 = -1;
	int v1 = -1;
	int h2 = -1;
	int v2 = -1;
	int h3 = -1;
	int v3 = -1;
	int h4 = -1;
	int v4 = -1;
	int h5 = -1;
	int v5 = -1;
	int h6 = -1;
	int v6 = -1;
	int h7 = -1;
	int v7 = -1;
	int h8 = -1;
	int v8 = -1;
	for (int i = 0; i < rev_mine.size(); i++)// checking to see if there are adjacent mines
	{
		auto a = rev_mine[i].getPosition();
		int h = a.x;
		int v = a.y;
		if (h == tilePos1x && v == tilePos1y)
		{
			h1 = tilePos1x;
			v1 = tilePos1y;
		}
		else if (h == tilePos2x && v == tilePos2y)
		{
			h2 = tilePos2x;
			v2 = tilePos2y;
		}
		else if (h == tilePos3x && v == tilePos3y)
		{
			h3 = tilePos3x;
			v3 = tilePos3y;
		}
		else if (h == tilePos4x && v == tilePos4y)
		{
			h4 = tilePos4x;
			v4 = tilePos4y;
		}
		else if (h == tilePos5x && v == tilePos5y)
		{
			h5 = tilePos5x;
			v5 = tilePos5y;
		}
		else if (h == tilePos6x && v == tilePos6y)
		{
			h6 = tilePos6x;
			v6 = tilePos6y;
		}
		else if (h == tilePos7x && v == tilePos7y)
		{
			h7 = tilePos7x;
			v7 = tilePos7y;
		}
		else if (h == tilePos8x && v == tilePos8y)
		{
			h8 = tilePos8x;
			v8 = tilePos8y;
		}

	}

	//if the coordinates I passed in do not have any adjacent mines then reveal the tile
	//if (revTest == true)
	//{
	rev_tile.push_back(Tile(xposition, yposition));

	//}

	if ((((h1 != tilePos1x) && (v1 != tilePos1y)) || ((h2 != tilePos2x) && (v2 != tilePos2y)) || ((h3 != tilePos3x) && (v3 != tilePos3y))) && revTest == true && (revtile1 == false && revtile2 == false) && (tilePos4x == 0 && tilePos4y == 0))
	{
		check(tilePos1x, tilePos1y, rev_mine, rev_tile, first, aa, revTest, adjacent_mines_or_revealed_tiles1, revtile1, flag);
		check(tilePos2x, tilePos2y, rev_mine, rev_tile, second, bb, revTest, adjacent_mines_or_revealed_tiles2, revtile2, flag);
		check(tilePos3x, tilePos3y, rev_mine, rev_tile, third, cc, revTest, adjacent_mines_or_revealed_tiles3, revtile3, flag);
		if (first == true && aa == true && adjacent_mines_or_revealed_tiles1 == false) { recursiontiles(tilePos1x, tilePos1y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (second == true && bb == true && adjacent_mines_or_revealed_tiles2 == false) { recursiontiles(tilePos2x, tilePos2y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (third == true && cc == true && adjacent_mines_or_revealed_tiles3 == false) { recursiontiles(tilePos3x, tilePos3y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
	}
	else if ((((h1 != tilePos1x) && (v1 != tilePos1y)) || ((h2 != tilePos2x) && (v2 != tilePos2y)) || ((h3 != tilePos3x) && (v3 != tilePos3y)) || ((h4 != tilePos4x) && (v4 != tilePos4y)) || ((h5 != tilePos5x) && (v5 != tilePos5y))) && revTest == true && (revtile1 == false && revtile2 == false && revtile3 == false && revtile4 == false && revtile5 == false) && (tilePos6x == 0 && tilePos6y == 0))
	{
		check(tilePos1x, tilePos1y, rev_mine, rev_tile, first, aa, revTest, adjacent_mines_or_revealed_tiles1, revtile1, flag);
		check(tilePos2x, tilePos2y, rev_mine, rev_tile, second, bb, revTest, adjacent_mines_or_revealed_tiles2, revtile2, flag);
		check(tilePos3x, tilePos3y, rev_mine, rev_tile, third, cc, revTest, adjacent_mines_or_revealed_tiles3, revtile3, flag);
		check(tilePos4x, tilePos4y, rev_mine, rev_tile, fourth, dd, revTest, adjacent_mines_or_revealed_tiles4, revtile4, flag);
		check(tilePos5x, tilePos5y, rev_mine, rev_tile, fifth, ee, revTest, adjacent_mines_or_revealed_tiles5, revtile5, flag);
		if (first == true && aa == true && adjacent_mines_or_revealed_tiles1 == false) { recursiontiles(tilePos1x, tilePos1y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (second == true && bb == true && adjacent_mines_or_revealed_tiles2 == false) { recursiontiles(tilePos2x, tilePos2y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (third == true && cc == true && adjacent_mines_or_revealed_tiles3 == false) { recursiontiles(tilePos3x, tilePos3y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (fourth == true && dd == true && adjacent_mines_or_revealed_tiles4 == false) { recursiontiles(tilePos4x, tilePos4y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (fifth == true && ee == true && adjacent_mines_or_revealed_tiles5 == false) { recursiontiles(tilePos5x, tilePos5y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
	}
	else if ((((h1 != tilePos1x) && (v1 != tilePos1y)) || ((h2 != tilePos2x) && (v2 != tilePos2y)) || ((h3 != tilePos3x) && (v3 != tilePos3y)) || ((h4 != tilePos4x) && (v4 != tilePos4y)) || ((h5 != tilePos5x) && (v5 != tilePos5y)) || ((h6 != tilePos6x) && (v6 != tilePos6y)) || ((h7 != tilePos7x) && (v7 != tilePos7y)) || ((h8 != tilePos8x) && (v8 != tilePos8y))) && revTest == true && (revtile1 == false && revtile2 == false && revtile3 == false && revtile4 == false && revtile5 == false && revtile6 == false && revtile7 == false && revtile8 == false) && (tilePos8x != 0 && tilePos8y != 0))
	{
		check(tilePos1x, tilePos1y, rev_mine, rev_tile, first, aa, revTest, adjacent_mines_or_revealed_tiles1, revtile1, flag);
		check(tilePos2x, tilePos2y, rev_mine, rev_tile, second, bb, revTest, adjacent_mines_or_revealed_tiles2, revtile2, flag);
		check(tilePos3x, tilePos3y, rev_mine, rev_tile, third, cc, revTest, adjacent_mines_or_revealed_tiles3, revtile3, flag);
		check(tilePos4x, tilePos4y, rev_mine, rev_tile, fourth, dd, revTest, adjacent_mines_or_revealed_tiles4, revtile4, flag);
		check(tilePos5x, tilePos5y, rev_mine, rev_tile, fifth, ee, revTest, adjacent_mines_or_revealed_tiles5, revtile5, flag);
		check(tilePos6x, tilePos6y, rev_mine, rev_tile, sixth, ff, revTest, adjacent_mines_or_revealed_tiles6, revtile6, flag);
		check(tilePos7x, tilePos7y, rev_mine, rev_tile, seventh, gg, revTest, adjacent_mines_or_revealed_tiles7, revtile7, flag);
		check(tilePos8x, tilePos8y, rev_mine, rev_tile, eighth, hh, revTest, adjacent_mines_or_revealed_tiles8, revtile8, flag);
		if (first == true && aa == true && adjacent_mines_or_revealed_tiles1 == false) { recursiontiles(tilePos1x, tilePos1y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (second == true && bb == true && adjacent_mines_or_revealed_tiles2 == false) { recursiontiles(tilePos2x, tilePos2y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (third == true && cc == true && adjacent_mines_or_revealed_tiles3 == false) { recursiontiles(tilePos3x, tilePos3y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (fourth == true && dd == true && adjacent_mines_or_revealed_tiles4 == false) { recursiontiles(tilePos4x, tilePos4y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (fifth == true && ee == true && adjacent_mines_or_revealed_tiles5 == false) { recursiontiles(tilePos5x, tilePos5y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (sixth == true && ff == true && adjacent_mines_or_revealed_tiles6 == false) { recursiontiles(tilePos6x, tilePos6y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (seventh == true && gg == true && adjacent_mines_or_revealed_tiles7 == false) { recursiontiles(tilePos7x, tilePos7y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
		if (eighth == true && hh == true && adjacent_mines_or_revealed_tiles8 == false) { recursiontiles(tilePos8x, tilePos8y, rev_mine, tile, adjacentTiles, rev_tile, recursioncounter, flag); }
	}


}

//For the check I need to make sure that I'm not drawing in tiles that are already filled out
void check(int& xposition, int& yposition, vector<Tile>& rev_mine, vector<Tile>& rev_tile, bool& value, bool& value2, bool& revTest, bool& adjacent_mines_or_revealed_tiles, bool& rev_adjacentTiles, vector<Tile>& flag)
{
	rev_adjacentTiles = false;
	adjacent_mines_or_revealed_tiles = false;
	value = true;
	value2 = true;
	for (int i = 0; i < rev_mine.size(); i++)
	{
		auto clickedTile = rev_mine[i].getPosition();
		int clickedTilex = clickedTile.x;
		int clickedTiley = clickedTile.y;
		if (clickedTilex == xposition && clickedTiley == yposition)
		{
			value = false;
			adjacent_mines_or_revealed_tiles = true;
			rev_adjacentTiles = true;
		}
	}
	for (int j = 0; j < rev_tile.size(); j++)
	{
		auto clickedTile = rev_tile[j].getPosition();
		int clickedTilex = clickedTile.x;
		int clickedTiley = clickedTile.y;
		if (clickedTilex == xposition && clickedTiley == yposition)
		{
			value = false;
			//revTest = false;
			adjacent_mines_or_revealed_tiles = true;
			//rev_adjacentTiles = true;
		}
	}
	for (int j = 0; j < flag.size(); j++)
	{
		auto clickedTile = flag[j].getPosition();
		int clickedTilex = clickedTile.x;
		int clickedTiley = clickedTile.y;
		if (clickedTilex == xposition && clickedTiley == yposition)
		{
			value = false;
			//revTest = false;
			adjacent_mines_or_revealed_tiles = true;
			rev_adjacentTiles = true;
		}
	}

}
void test(string& path, vector<Tile>& rev_tile, vector<Tile>& rev_mine, vector<Tile*>& adjacentTiles, vector<Tile>& flag, vector<Tile>& sec_mine, vector<Tile>& tile, int& COUNTER)
{
	vector<char> temporary;
	int test_counter = 0;
	rev_tile.erase(rev_tile.begin(), rev_tile.begin() + rev_tile.size());
	rev_mine.erase(rev_mine.begin(), rev_mine.begin() + rev_mine.size());
	adjacentTiles.erase(adjacentTiles.begin(), adjacentTiles.begin() + rev_tile.size());
	flag.erase(flag.begin(), flag.begin() + flag.size());
	sec_mine.erase(sec_mine.begin(), sec_mine.begin() + sec_mine.size());

	ifstream inFile(path);
	if (inFile.is_open())
	{
		string lineFromFile;
		while (getline(inFile, lineFromFile))
		{
			istringstream stream(lineFromFile);
			string buffer;

			getline(stream, buffer, ' ');

			char Number[25];
			for (int i = 0; i < buffer.length(); i++)
			{
				//string v = buffer[i];
				//int intconversion = stoi(buffer[i]);
				Number[i] = buffer[i];
				//cout << Number[i] << " : " <<buffer[i] << endl;
			}
			for (int i = 0; i < buffer.size(); i++)
			{
				//cout << Number[i];
				char x = Number[i];
				temporary.push_back(x);
				test_counter++;
			}

		}
		for (int i = 0; i < temporary.size(); i++)
		{
			if (temporary[i] == '1')
			{
				auto clickedTile = tile[i].getPosition();
				int clickedTilex = clickedTile.x;
				int clickedTiley = clickedTile.y;
				rev_mine.push_back(Tile(clickedTilex, clickedTiley));
			}
		}
		//for (int i = 0; i < tile.size(); i++)
		//{
		Tile getPointers;
		getPointers.Update(tile, adjacentTiles);
		//}
		COUNTER = rev_mine.size();
		temporary.erase(temporary.begin(), temporary.begin() + temporary.size());
	}
}
void moremines(vector<Tile>& rev_mine)
{
	bool noduplication = true;
	int k = 0;
	for (int i = 0; i < rev_mine.size(); i++)
	{

		auto a = rev_mine[i].getPosition();
		int h = a.x;

		int v = a.y;
		for (int j = 0; j < rev_mine.size(); j++)
		{
			auto aa = rev_mine[j].getPosition();
			int hh = aa.x;
			int vv = aa.y;
			if (h == hh && v == vv && j != i && noduplication == true)
			{

				noduplication = false;
				k = j;
				//mt19937 random_mt(time(0));

			}
		}
	}
	if (noduplication == false)
	{
		rev_mine.erase(rev_mine.begin() + (k));
	}
	for (int i = rev_mine.size(); i < 50; i++)
	{
		int horizontal_position = Random(0, ((24) * 32));
		horizontal_position = reductionx(horizontal_position);
		//rev_tile.push_back(revealedTile(i,j));

		int vertical_position = Random(0, ((15) * 32));
		vertical_position = reductiony(vertical_position);

		rev_mine.push_back(Tile(horizontal_position, vertical_position));
	}
	if (noduplication == false)
	{
		moremines(rev_mine);
	}

}
void Draw_Numbers(int& xposition, int& yposition, vector<Tile>& tile, vector<Tile>& rev_tile, vector<Tile>& rev_mine, vector<Tile*>& adjacentTiles, vector<Tile>& number, vector<int>& num1)
{
	//determine the tile position that I am going to want to access when getting adjacent mines
	int j = 0;
	for (int uz = 0; uz < tile.size(); uz++)
	{
		auto uniquea = tile[uz].getPosition();
		int uniqueh = uniquea.x;
		int uniquev = uniquea.y;
		if (xposition == uniqueh && yposition == uniquev)
		{
			j = uz;
		}
	}
	//End previous step

	//Get tile positions of adjacent tiles
	auto tilePos1 = adjacentTiles[j]->data1;
	int tilePos1x = tilePos1.x;
	int tilePos1y = tilePos1.y;

	auto tilePos2 = adjacentTiles[j]->data2;
	int tilePos2x = tilePos2.x;
	int tilePos2y = tilePos2.y;

	auto tilePos3 = adjacentTiles[j]->data3;
	int tilePos3x = tilePos3.x;
	int tilePos3y = tilePos3.y;

	auto tilePos4 = adjacentTiles[j]->data4;
	int tilePos4x = tilePos4.x;
	int tilePos4y = tilePos4.y;

	auto tilePos5 = adjacentTiles[j]->data5;
	int tilePos5x = tilePos5.x;
	int tilePos5y = tilePos5.y;

	auto tilePos6 = adjacentTiles[j]->data6;
	int tilePos6x = tilePos6.x;
	int tilePos6y = tilePos6.y;

	auto tilePos7 = adjacentTiles[j]->data7;
	int tilePos7x = tilePos7.x;
	int tilePos7y = tilePos7.y;

	auto tilePos8 = adjacentTiles[j]->data8;
	int tilePos8x = tilePos8.x;
	int tilePos8y = tilePos8.y;
	//end this step

	//check to see if adjacent tiles have mines
	int h1 = -1;
	int v1 = -1;
	int h2 = -1;
	int v2 = -1;
	int h3 = -1;
	int v3 = -1;
	int h4 = -1;
	int v4 = -1;
	int h5 = -1;
	int v5 = -1;
	int h6 = -1;
	int v6 = -1;
	int h7 = -1;
	int v7 = -1;
	int h8 = -1;
	int v8 = -1;
	for (int i = 0; i < rev_mine.size(); i++)// checking to see if there are adjacent mines
	{
		auto a = rev_mine[i].getPosition();
		int h = a.x;
		int v = a.y;
		if (h == tilePos1x && v == tilePos1y)
		{
			h1 = tilePos1x;
			v1 = tilePos1y;
		}
		else if (h == tilePos2x && v == tilePos2y)
		{
			h2 = tilePos2x;
			v2 = tilePos2y;
		}
		else if (h == tilePos3x && v == tilePos3y)
		{
			h3 = tilePos3x;
			v3 = tilePos3y;
		}
		else if (h == tilePos4x && v == tilePos4y && (tilePos4x != 0 && tilePos4y != 0))
		{
			h4 = tilePos4x;
			v4 = tilePos4y;
		}
		else if (h == tilePos5x && v == tilePos5y && (tilePos5x != 0 && tilePos5y != 0))
		{
			h5 = tilePos5x;
			v5 = tilePos5y;
		}
		else if (h == tilePos6x && v == tilePos6y && (tilePos6x != 0 && tilePos6y != 0))
		{
			h6 = tilePos6x;
			v6 = tilePos6y;
		}
		else if (h == tilePos7x && v == tilePos7y && (tilePos7x != 0 && tilePos7y != 0))
		{
			h7 = tilePos7x;
			v7 = tilePos7y;
		}
		else if (h == tilePos8x && v == tilePos8y && (tilePos8x != 0 && tilePos8y != 0))
		{
			h8 = tilePos8x;
			v8 = tilePos8y;
		}
	}
	//end this step

		//number.push_back(Tile(xposition, yposition));
	int num_adj_tile = 0;
	if ((h1 == tilePos1x) && (v1 == tilePos1y)) { num_adj_tile++; }
	if ((h2 == tilePos2x) && (v2 == tilePos2y)) { num_adj_tile++; }
	if ((h3 == tilePos3x) && (v3 == tilePos3y)) { num_adj_tile++; }
	if ((h4 == tilePos4x) && (v4 == tilePos4y)) { num_adj_tile++; }
	if ((h5 == tilePos5x) && (v5 == tilePos5y)) { num_adj_tile++; }
	if ((h6 == tilePos6x) && (v6 == tilePos6y)) { num_adj_tile++; }
	if ((h7 == tilePos7x) && (v7 == tilePos7y)) { num_adj_tile++; }
	if ((h8 == tilePos8x) && (v8 == tilePos8y)) { num_adj_tile++; }
	if (num_adj_tile != 0) {
		number.push_back(Tile(xposition, yposition));
		num1.push_back(num_adj_tile);
	}
	//am_i_out_of_forloop = false;

}