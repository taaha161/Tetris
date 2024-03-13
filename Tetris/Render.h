#pragma once
#include "Tetris.h"

class Render {
private:
    TetriminoI I;
    TetriminoJ J;
    TetriminoL L;
    TetriminoO O;
    TetriminoS S;
    TetriminoT T;
    TetriminoZ Z;
    Tetrimino** RandomTetrimino;
public:
    Render() {
        
        Tetrimino** RandomTetrimino = new Tetrimino * [7];
        RandomTetrimino[0] = &I;
        RandomTetrimino[1] = &J;
        RandomTetrimino[2] = &L;
        RandomTetrimino[3] = &O;
        RandomTetrimino[4] = &S;
        RandomTetrimino[5] = &T;
        RandomTetrimino[6] = &Z;
        cout << "Constructor Called Successfully";
    }
    Tetrimino& GetTetrimino(int i) {
        cout << "error";
        return *(RandomTetrimino[i]);
    }
    ~Render() {
        for (int i = 0; i < 7; i++) {
            RandomTetrimino[i] = nullptr;
        }
        delete[]RandomTetrimino;
    }
};