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
    string chessType = "0";
    int index = 0;
    bool canMove = false;
    bool ifWhiteKingMove = false;
    bool ifBlackKingMove = false;
    bool ifPawnMove2Step = false;
    bool inPawnNextTurn = false;
    bool ifRookMove = false;
    bool ifPawnPromoting = false;
    string promotingType = "0";
};

#endif // SAVEALLINFORMATION_H
