#include <iostream>
#include "Game.h"
#include "SFML/Audio.hpp"

#include <cstdlib>
#include <time.h>
#include "Tetris.h"
#include "Scoring.h"
using namespace std;

int main()
{   


    sf::Font font;
    sf::Texture EndGame;
    HighScores highScore;
    
    if (!font.loadFromFile("Minecrafter.Reg.ttf")) {
        cout << "Error Loading Font";
    }
  
    sf::Text name;
    name.setFont(font);
    string Player;
    cout << "Enter Your Name" << endl;
    cin >> Player;
    name.setString("Name : " + Player);
    name.setCharacterSize(50);
    name.setFillColor(sf::Color::Black);
    name.setPosition(1000, 300);
    sf::Text LevelNo;
    LevelNo.setFont(font);
    LevelNo.setCharacterSize(50);
    LevelNo.setFillColor(sf::Color::Black);
    LevelNo.setPosition(1000, 600);

    sf::Text LineNo;
    LineNo.setFont(font);
    LineNo.setCharacterSize(50);
    LineNo.setFillColor(sf::Color::Black);
    LineNo.setPosition(1000, 900);
    
    sf::Text ScoreDisplay;
    ScoreDisplay.setFont(font);
    ScoreDisplay.setCharacterSize(50);
    ScoreDisplay.setFillColor(sf::Color::Black);
    ScoreDisplay.setPosition(1000, 1200);


    sf::RenderWindow window(sf::VideoMode(1500, 1500), "My window");
    TetriminoI *I = new TetriminoI;
    TetriminoJ *J = new TetriminoJ;
    TetriminoL *L = new TetriminoL;
    TetriminoO *O = new TetriminoO;
    TetriminoS *S = new TetriminoS;
    TetriminoT *T = new TetriminoT;
    TetriminoZ *Z = new TetriminoZ;
    Tetrimino** RandomTetrimino = new Tetrimino * [7];

    RandomTetrimino[0] = I;
    RandomTetrimino[1] = J;
    RandomTetrimino[2] = L;
    RandomTetrimino[3] = O;
    RandomTetrimino[4] = S;
    RandomTetrimino[5] = T;
    RandomTetrimino[6] = Z;
    srand(time(0));
    int TetriminoNumber =  rand() % 7;
    

    well well;
    fall fall;
    sf::Clock clock;
    sf::Time t1;
    level level;
    sf::Music happi;
    if (!happi.openFromFile("happi.wav")) {
        cout << "Could not load music ";
    }
    happi.play();
    while (window.isOpen())
    {
        
        int speed = level.GetLevel() * 1.10;
        LevelNo.setString("Level: " + to_string(level.GetLevel()));
        LineNo.setString("Lines: " + to_string(fall.getLines()));
        ScoreDisplay.setString("Score: " + to_string(fall.getScore()));
        int x = 1;
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
       
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                   (RandomTetrimino[TetriminoNumber])->Rotate(well);
                 
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    (RandomTetrimino[TetriminoNumber])->LeftMove(well);
                  
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    (RandomTetrimino[TetriminoNumber])->RightMove(well);
                   
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down) {
                  x =  (RandomTetrimino[TetriminoNumber])->downFast(well);
                 
                }
                if (x == 0) {
                    break;
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 8; j++) {
                window.draw(well.draw(i, j));
            }
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                window.draw((RandomTetrimino[TetriminoNumber])->draw(i, j));
            }
        }
        
      
      
        //Sleep(1000);
        t1 = clock.getElapsedTime();
       
        if (t1 >= sf::seconds(2 )) {
            // do nothing
            x = fall.down((RandomTetrimino[TetriminoNumber])->I, well);
            clock.restart();
        }
        // end the current frame
    
            if ( x == 0) {

                well.WellRedraw((RandomTetrimino[TetriminoNumber])->I);
                delete I;
                delete J;
                delete L;
                delete O;
                delete S;
                delete T;
                delete Z;
                I = new TetriminoI;
                J = new TetriminoJ;
                L = new TetriminoL;
                O = new TetriminoO;
                S = new TetriminoS;
                T = new TetriminoT;
                Z = new TetriminoZ;
                RandomTetrimino[0] = I;
                RandomTetrimino[1] = J;
                RandomTetrimino[2] = L;
                RandomTetrimino[3] = O;
                RandomTetrimino[4] = S;
                RandomTetrimino[5] = T;
                RandomTetrimino[6] = Z;
                //  (RandomTetrimino[TetriminoNumber])->RecreateShape();
                TetriminoNumber = rand() % 7;

            
        }
        window.draw(name);
        window.draw(LevelNo);
        window.draw(LineNo);
        window.draw(ScoreDisplay);
       
        window.display();

        if (fall.getLines() % 10 == 0 && fall.getLines() != 0) {
            //level.IncreseLevel();
            fall.resetLines();
        }
        if (fall.GameOver(well)) {

            highScore.setHighscores();
            highScore.UpdateHighScore(fall.getScore());
            highScore.getHighscores();
           
            if (!EndGame.loadFromFile("GAMEOVER.jpg")) {
                cout << "Error Loading image";
            }
            sf::Sprite sprite;
            sprite.setTexture(EndGame);
            sprite.setPosition(300, 300);
            sprite.scale(1.5, 1.5);
            window.draw(sprite);
            window.display();
            cout << "Game Over";
            system("pause");
           
         
       }
       
        fall.CleanUp(well);
       
    }
   
    return 0;
}