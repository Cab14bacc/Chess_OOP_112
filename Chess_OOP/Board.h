#include <string>
#ifndef BOARD_H
#define BOARD_H

using namespace std;

class Board
{
public:
    Board();
    bool ifHavePiece;//if there a chess piece
    int wTarget;//how many white piece can attack
    int bTarget;//how many black piece can attack
    char player;
    string chessType;
    int index;
};

#endif // BOARD_H
