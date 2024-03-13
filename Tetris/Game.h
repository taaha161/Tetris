#pragma once
#include "Tetris.h"
#include "Scoring.h"
#include "Well.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include<Windows.h>
#include <vector>
using namespace std;
class fall {
	score Score;
	int lines =0;
public:
	int down(sf::RectangleShape I[][5], well &obj) {

		int Bottommost = 0;
		int x, y;
		bool AllowMoveDown = true;
		sf::RectangleShape BottomMostRectangle;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (I[i][j].getFillColor() != sf::Color:: Transparent) {
					if (I[i][j].getPosition().y > Bottommost) {
						Bottommost = I[i][j].getPosition().y;
						BottomMostRectangle = I[i][j];
						x = i;
						y = j;
						
					}
				}


			}
		}
		// Calculating next cell
	
		cout << AllowMoveDown;
		if (Bottommost < 1400 && AllowMoveDown ) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					
					I[i][j].setPosition(sf::Vector2f(I[i][j].getPosition().x, I[i][j].getPosition().y + 100));
					
					


				}
			}

			if (collision(I, obj)) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {

						I[i][j].setPosition(sf::Vector2f(I[i][j].getPosition().x, I[i][j].getPosition().y - 100));




					}
				}
				return 0;
			}
			return 1;
		}
		else {
			
			return 0;
		}
	}


	bool collision(sf::RectangleShape I[][5], well& obj) {

		vector <sf::Vector2f> ColoredCells;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 8; j++) {
				if (obj.Well[i][j].getFillColor() != sf::Color::White) {
					ColoredCells.push_back(obj.Well[i][j].getPosition());
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (I[i][j].getFillColor() != sf::Color::Transparent) {
					for (int k = 0; k < ColoredCells.size(); k++)
					{
						if (I[i][j].getPosition() == ColoredCells[k]) {
							return true;
						}
					}
				}
			}
		}
		
		return false;


	}

	bool GameOver(well& obj) {
		for (int i = 0; i < 8; i++) {
			if (obj.Well[0][i].getFillColor() != sf::Color::White) {
				return true;
			}
		}
		return false;
	}
	void CleanUp(well& obj) {
		bool clean = true;
		int rowClean;
		for (int i = 0; i < 15; i++) {
			clean = true;
			rowClean = i;
			for (int j = 0; j < 8; j++) {
				if (obj.Well[i][j].getFillColor() == sf::Color::White) {
					clean = false;
					break;
				}
			
			}

			if (clean == true) {
				cout << "Cleaning Row Number " << rowClean;
				Score.AddScore(100);
				lines++;
				for (int l = rowClean; l > 0; l--) {
					for (int k = 0; k < 8; k++) {
						sf::Color bgColor = obj.Well[l - 1][k].getFillColor();
						obj.Well[l][k].setFillColor(bgColor);
						
					}
				}
				
			}

		}
		
	}
	int getScore() {
		return Score.getScore();
	}
	int getLines() {
		return lines;
	}
	void resetLines() {
		lines = 0;
	}
	
};

