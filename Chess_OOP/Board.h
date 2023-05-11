<<<<<<< HEAD
=======

#ifndef BOARD_H
#define BOARD_H
class Board
{
public:
    bool ifHavePiece;//if there a chess piece
    int wTarget;//how many white piece can attack
    int bTarget;//how many black piece can attack
    void setIfHavePiece(bool piece);
    void plusWTarget();
    void plusBTarget();
};

#endif // BOARD_H
>>>>>>> 31dbd3d3940833b5f08818f48a2476d4e8aca63c
