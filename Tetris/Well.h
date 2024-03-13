#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
class well {

public:
	sf::RectangleShape Well[20][15];
	well() {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 8; j++) {
				sf::RectangleShape BGrect(sf::Vector2f(50, 50));
				BGrect.setOutlineColor(sf::Color::Black);
				BGrect.setOutlineThickness(20);
				BGrect.setFillColor(sf::Color::White);
				BGrect.setPosition(100 * j, 100 * i);
				Well[i][j] = BGrect;
			}
		}

	}
	sf::RectangleShape draw(int i, int j) {
		return	Well[i][j];
	}
	void WellRedraw(sf::RectangleShape I[][5]) {
		cout << "New well" << endl;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 8; j++) {
				for (int k = 0; k < 5; k++) {
					for (int l = 0; l < 5; l++) {
						if (Well[i][j].getPosition() == I[k][l].getPosition() && I[k][l].getFillColor() != sf::Color::Transparent) {
							cout << "Color change called" << endl;
							sf::RectangleShape BGrect(sf::Vector2f(50, 50));
							BGrect.setOutlineColor(sf::Color::Black);
							BGrect.setOutlineThickness(20);
							sf::Color bg = I[k][l].getFillColor();
							BGrect.setFillColor(bg);
							BGrect.setPosition(I[k][l].getPosition());
							Well[i][j] = BGrect;
						}
						
					}
				}

			}
		}
	}
	
};