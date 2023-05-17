#include <iostream>
#ifndef SAVEALLINFORMATION_H
#define SAVEALLINFORMATION_H

using namespace std;

class SaveAllInformation
{
public:
    bool ifHavePiece = false;//if there a chess piece
    int wTarget = 0;//how many white piece can attack
    int bTarget = 0;//how many black piece can attack
    char player = '0';//this chess belong to which player
    string chessType = "0";//save chess type
    int index = 0;//save chess index
    bool canMove = false;//save this pos if can move
    bool ifPawnMove2Step = false;//save pawn if move two step
    bool inPawnNextTurn = false;//save if this turn is after pawn move two step
    bool ifRookMove = false;//if rook have been moved
    bool ifPawnPromoting = false;//if pawn promoted
    string promotingType = "0";// if pawn have been promoted, save promoting type
};

#endif // SAVEALLINFORMATION_H
