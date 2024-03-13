#pragma once
#include<SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include "Well.h"
#include <iostream>
using namespace std;

class Tetrimino  {
	int leftmost;
	int Rightmost;
	friend class well;
public:
	sf::RectangleShape I[5][5];

	Tetrimino() {
		//Drawing base 5x5 Grid of Rectangles
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				I[i][j] = Tetrimino::drawBaseRectangle(j * 100, i * 100);

			}
		}
	}
	
	
	// Base Reactangles of Color : Transparent 180461
	sf:: RectangleShape drawBaseRectangle(int x, int y) {
		 sf::RectangleShape _rectangle(sf::Vector2f(50, 50));
		_rectangle.setFillColor(sf::Color:: Transparent);
		_rectangle.setPosition(x, y);
		
		return _rectangle;
	}

	//Reset Shape to default
	void ResetShape() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				I[i][j] = Tetrimino::drawBaseRectangle(j * 100, i * 100);

			}
		}

	}
	// Draw Tetriminos
	virtual sf::RectangleShape draw(int i, int j) {
		return I[i][j];
	}
	virtual void RightMove(well &obj) {
		Rightmost = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (I[i][j].getFillColor() != sf::Color::Transparent) {
					
					if (I[i][j].getPosition().x > Rightmost) {
						Rightmost = I[i][j].getPosition().x;
					}
				}


			}
		}

		if (Rightmost < 700) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					I[i][j].move(100, 0);


				}
			}
			if (collision(I,obj)) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						I[i][j].move(-100, 0);


					}
				}
			}
		}
		
	}
	virtual void LeftMove(well &obj) {
		leftmost = 1000;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (I[i][j].getFillColor() != sf::Color::Transparent) {
					
					if (I[i][j].getPosition().x < leftmost) {
						leftmost = I[i][j].getPosition().x;
					}
				}


			}
		}

		if (leftmost > 0 ) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					I[i][j].move(-100, 0);


				}
			}
			if (collision(I,obj)) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						I[i][j].move(100, 0);


					}
				}
				
			}
		}
		
	}

	virtual	bool downFast( well &obj) {
		int Bottommost = 0;
		int x, y;
		bool AllowMoveDown = true;
		sf::RectangleShape BottomMostRectangle;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (I[i][j].getFillColor() != sf::Color::Transparent) {
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
		if (Bottommost < 1400 && AllowMoveDown) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {

					I[i][j].setPosition(sf::Vector2f(I[i][j].getPosition().x, I[i][j].getPosition().y + 100));




				}
			}

			if (collision(I, obj)) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						I[i][j].move(0, -100);


					}
				}
				return 0;
			}
		}
		else {
			return 0;
		}
		return 1;

	}

	virtual void Rotate(well &obj) {
		Tetrimino I2;
		static int rotation = 0;
		sf::Vector2f pivot;

		pivot.x = I[2][2].getPosition().x;
		pivot.y = I[2][2].getPosition().y;
		

		
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {

					sf::Vector2f position = I[i][j].getPosition();
					position.x = position.x - pivot.x;
					position.y -= pivot.y;
					sf::Vector2f temp;
					temp.x = -position.y;
					temp.y = position.x;
					temp.x += pivot.x;
					temp.y += pivot.y;
					sf::Color bg = I[i][j].getFillColor();
					sf::RectangleShape rectangle(sf::Vector2f(50, 50));
					rectangle.setFillColor(bg);
					rectangle.setPosition(temp.x, temp.y);


					I2.I[i][j] = rectangle;



				}
			}

		
		
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				while (I2.I[i][j].getPosition().x > 700 || I2.I[i][j].getPosition().y > 1500 || I2.I[i][j].getPosition().x < 0 || I2.I[i][j].getPosition().y < 0) {

					if (I2.I[i][j].getPosition().x > 700) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(-100, 0));
							}
						}
					}
					else if (I2.I[i][j].getPosition().y > 1500)
					{
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, -100));
							}
						}
					}
					else if (I2.I[i][j].getPosition().x < 0) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(+100, 0));
							}
						}
					}
					else {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, +100));
							}
						}
					}

				}
			}
		}
		if (!collision(I2.I, obj)) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {

					I[i][j] = I2.I[i][j];

				}
			}
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

	void center() {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				I[i][j].move(200, 0);
			}
		}
	}
	
};

class TetriminoI : public Tetrimino{

	
public:
	TetriminoI() {
		int j = 0;
		for (int i = 0; i < 5; i++) {
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setPosition(100, 0+j);
			I[i][1] = rectangle;
			
			j += 100;
		}
		
		center();
	}





};

class TetriminoJ : public Tetrimino {
public:
	
	TetriminoJ() {
		ResetShape();
		int j = 0;
		for (int i = 0; i < 5; i++) {
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Yellow);
			rectangle.setPosition(100, 0 + j);
			I[i][1] = rectangle;

			j += 100;
		}
		sf::RectangleShape rectangle(sf::Vector2f(50, 50));
		rectangle.setFillColor(sf::Color::Yellow);
		rectangle.setPosition(0, j - 100);
		I[4][0] = rectangle;
	}
	void Rotate() {
		Tetrimino I2;
		static int rotation = 0;
		sf::Vector2f pivot;

		pivot.x = I[2][1].getPosition().x;
		pivot.y = I[2][1].getPosition().y;
		/*if (pivot.x > 1000 || pivot.y > 1000) {
			pivot.x = I[2][0].getPosition().x;
			pivot.y = I[2][0].getPosition().y;
		}*/

		cout << "The pivot is " << pivot.x << " " << pivot.y;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				sf::Vector2f position = I[i][j].getPosition();
				position.x = position.x - pivot.x;
				position.y -= pivot.y;
				sf::Vector2f temp;
				temp.x = -position.y;
				temp.y = position.x;
				temp.x += pivot.x;
				temp.y += pivot.y;
				sf::Color bg = I[i][j].getFillColor();
				sf::RectangleShape rectangle(sf::Vector2f(100, 100));
				rectangle.setFillColor(bg);
				rectangle.setPosition(temp.x, temp.y);

				
				I2.I[i][j] = rectangle;



			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				while (I2.I[i][j].getPosition().x > 800 || I2.I[i][j].getPosition().y > 1500 || I2.I[i][j].getPosition().x < 0 || I2.I[i][j].getPosition().y < 0) {

					if (I2.I[i][j].getPosition().x > 800) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(-150, 0));
							}
						}
					}
					else if (I2.I[i][j].getPosition().y > 1500)
					{
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, -150));
							}
						}
					}
					else if (I2.I[i][j].getPosition().x < 0) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(+150, 0));
							}
						}
					}
					else {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, +150));
							}
						}
					}

				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				I[i][j] = I2.I[i][j];

			}
		}
		center();
	}

	
};

class TetriminoL : public Tetrimino {
public:
	TetriminoL() {
		ResetShape();
		int j = 0;
		for (int i = 0; i < 5; i++) {
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Yellow);
			rectangle.setPosition(100, 0 + j);
			I[i][1] = rectangle;

			j += 100;
		}
		sf::RectangleShape rectangle(sf::Vector2f(50, 50));
		rectangle.setFillColor(sf::Color::Yellow);
		rectangle.setPosition(200, j - 100);
		I[4][2] = rectangle;
		center();
	}

	void Rotate() {
		Tetrimino I2;
		static int rotation = 0;
		sf::Vector2f pivot;

		pivot.x = I[2][1].getPosition().x;
		pivot.y = I[2][1].getPosition().y;
		/*if (pivot.x > 1000 || pivot.y > 1000) {
			pivot.x = I[2][0].getPosition().x;
			pivot.y = I[2][0].getPosition().y;
		}*/

		cout << "The pivot is " << pivot.x << " " << pivot.y;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				sf::Vector2f position = I[i][j].getPosition();
				position.x = position.x - pivot.x;
				position.y -= pivot.y;
				sf::Vector2f temp;
				temp.x = -position.y;
				temp.y = position.x;
				temp.x += pivot.x;
				temp.y += pivot.y;
				sf::Color bg = I[i][j].getFillColor();
				sf::RectangleShape rectangle(sf::Vector2f(100, 100));
				rectangle.setFillColor(bg);
				rectangle.setPosition(temp.x, temp.y);

				if (bg == bg) {
					cout << "x coordinate = " << temp.y << endl;
					cout << "y coordinate = " << temp.x << endl;
				}
				I2.I[i][j] = rectangle;



			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				while (I2.I[i][j].getPosition().x > 800 || I2.I[i][j].getPosition().y > 1500 || I2.I[i][j].getPosition().x < 0 || I2.I[i][j].getPosition().y < 0) {

					if (I2.I[i][j].getPosition().x > 800) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(-100, 0));
							}
						}
					}
					else if (I2.I[i][j].getPosition().y > 1500)
					{
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, -100));
							}
						}
					}
					else if (I2.I[i][j].getPosition().x < 0) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(+100, 0));
							}
						}
					}
					else {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, +100));
							}
						}
					}

				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				I[i][j] = I2.I[i][j];

			}
		}

	}

	
};
class TetriminoO : public Tetrimino {

public:
	TetriminoO() {
		
		ResetShape();
		int j = 0;
		for (int i = 1; i < 3; i++) {
			cout << "Loop run";
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(j + 100, 100);
			I[1][i] = rectangle;

			j += 100;
		}
		j = 0;
		for (int i = 1; i < 3; i++) {
			cout << "Loop run";
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(j + 100, 200);

			I[2][i] = rectangle;

			j += 100;
		}
		center();
	}

	void Rotate(well& obj) {
		cout << endl << "Do nothing";
	}
	
};
class TetriminoS : public Tetrimino {

public:
	TetriminoS() {
		ResetShape();
		int j = 0;
		for (int i = 1; i < 3; i++) {
			cout << "Loop run";
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(j + 100, 100);

			I[1][i] = rectangle;

			j += 100;
		}
		j = -100;
		for (int i = 2; i < 4; i++) {
			cout << "Loop run";
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(j + 100, 200);

			I[2][i] = rectangle;

			j += 100;
		}
		center();
	}
	void Rotate() {
		Tetrimino I2;
		static int rotation = 0;
		sf::Vector2f pivot;

		pivot.x = I[2][3].getPosition().x;
		pivot.y = I[2][3].getPosition().y;
		/*if (pivot.x > 1000 || pivot.y > 1000) {
			pivot.x = I[2][0].getPosition().x;
			pivot.y = I[2][0].getPosition().y;
		}*/

		cout << "The pivot is " << pivot.x << " " << pivot.y;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				sf::Vector2f position = I[i][j].getPosition();
				position.x = position.x - pivot.x;
				position.y -= pivot.y;
				sf::Vector2f temp;
				temp.x = -position.y;
				temp.y = position.x;
				temp.x += pivot.x;
				temp.y += pivot.y;
				sf::Color bg = I[i][j].getFillColor();
				sf::RectangleShape rectangle(sf::Vector2f(100, 100));
				rectangle.setFillColor(bg);
				rectangle.setPosition(temp.x, temp.y);

				if (bg == bg) {
					cout << "x coordinate = " << temp.y << endl;
					cout << "y coordinate = " << temp.x << endl;
				}
				I2.I[i][j] = rectangle;



			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				while (I2.I[i][j].getPosition().x > 800 || I2.I[i][j].getPosition().y > 1500 || I2.I[i][j].getPosition().x < 0 || I2.I[i][j].getPosition().y < 0) {

					if (I2.I[i][j].getPosition().x > 800) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(-100, 0));
							}
						}
					}
					else if (I2.I[i][j].getPosition().y > 1500)
					{
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, -100));
							}
						}
					}
					else if (I2.I[i][j].getPosition().x < 0) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(+100, 0));
							}
						}
					}
					else {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, +100));
							}
						}
					}

				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				I[i][j] = I2.I[i][j];

			}
		}

	}

	

};
class TetriminoT : public Tetrimino {
public:
	TetriminoT() {
		ResetShape();
		int j = 0;
		for (int i = 1; i < 4; i++) {
			cout << "Loop run";
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(j + 100, 100);

			I[1][i] = rectangle;

			j += 100;
		}
		sf::RectangleShape rectangle(sf::Vector2f(50, 50));
		rectangle.setFillColor(sf::Color::Red);
		rectangle.setPosition(200, 200);
		I[2][2] = rectangle;
		center();
	}
	void Rotate() {
		Tetrimino I2;
		static int rotation = 0;
		sf::Vector2f pivot;

		pivot.x = I[2][1].getPosition().x;
		pivot.y = I[2][1].getPosition().y;


		cout << "The pivot is " << pivot.x << " " << pivot.y;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				sf::Vector2f position = I[i][j].getPosition();
				position.x = position.x - pivot.x;
				position.y -= pivot.y;
				sf::Vector2f temp;
				temp.x = -position.y;
				temp.y = position.x;
				temp.x += pivot.x;
				temp.y += pivot.y;
				sf::Color bg = I[i][j].getFillColor();
				sf::RectangleShape rectangle(sf::Vector2f(100, 100));
				rectangle.setFillColor(bg);
				rectangle.setPosition(temp.x, temp.y);

				if (bg == bg) {
					cout << "x coordinate = " << temp.y << endl;
					cout << "y coordinate = " << temp.x << endl;
				}
				I2.I[i][j] = rectangle;



			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				while (I2.I[i][j].getPosition().x > 800 || I2.I[i][j].getPosition().y > 1500 || I2.I[i][j].getPosition().x < 0 || I2.I[i][j].getPosition().y < 0) {

					if (I2.I[i][j].getPosition().x > 800) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(-100, 0));
							}
						}
					}
					else if (I2.I[i][j].getPosition().y > 1500)
					{
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, -100));
							}
						}
					}
					else if (I2.I[i][j].getPosition().x < 0) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(+100, 0));
							}
						}
					}
					else {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, +100));
							}
						}
					}

				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				I[i][j] = I2.I[i][j];

			}
		}

	}


};
class TetriminoZ : public Tetrimino {
public:
	TetriminoZ() {
		ResetShape();
		int j = 0;
		for (int i = 1; i < 3; i++) {
			cout << "Loop run";
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(j + 100, 100);

			I[1][i] = rectangle;

			j += 100;
		}
		j = 100;
		for (int i = 2; i < 4; i++) {
			cout << "Loop run";
			sf::RectangleShape rectangle(sf::Vector2f(50, 50));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(j + 100, 200);

			I[2][i] = rectangle;

			j += 100;
		}
		center();
	}
	void Rotate() {
		Tetrimino I2;
		static int rotation = 0;
		sf::Vector2f pivot;

		pivot.x = I[2][2].getPosition().x;
		pivot.y = I[2][2].getPosition().y;
		
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				sf::Vector2f position = I[i][j].getPosition();
				position.x = position.x - pivot.x;
				position.y -= pivot.y;
				sf::Vector2f temp;
				temp.x = -position.y;
				temp.y = position.x;
				temp.x += pivot.x;
				temp.y += pivot.y;
				sf::Color bg = I[i][j].getFillColor();
				sf::RectangleShape rectangle(sf::Vector2f(100, 100));
				rectangle.setFillColor(bg);
				rectangle.setPosition(temp.x, temp.y);

				if (bg == bg) {
					cout << "x coordinate = " << temp.y << endl;
					cout << "y coordinate = " << temp.x << endl;
				}
				I2.I[i][j] = rectangle;



			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				while (I2.I[i][j].getPosition().x > 800 || I2.I[i][j].getPosition().y > 1500 || I2.I[i][j].getPosition().x < 0 || I2.I[i][j].getPosition().y < 0) {

					if (I2.I[i][j].getPosition().x > 800) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(-100, 0));
							}
						}
					}
					else if (I2.I[i][j].getPosition().y > 1500)
					{
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, -100));
							}
						}
					}
					else if (I2.I[i][j].getPosition().x < 0) {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(+100, 0));
							}
						}
					}
					else {
						for (int x = 0; x < 5; x++) {
							for (int y = 0; y < 5; y++) {
								I2.I[x][y].move(sf::Vector2f(0, +100));
							}
						}
					}

				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {

				I[i][j] = I2.I[i][j];

			}
		}

	}

	
};
