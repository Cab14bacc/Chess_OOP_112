#include <string>
#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

using namespace std;

class ViewManager
{
public:
    ViewManager();
    bool ifHavePiece;//if there a chess piece
    int wTarget;//how many white piece can attack
    int bTarget;//how many black piece can attack
    char player;//this chess belong to which player
    string chessType;//save chess type
    int index;//save chess index
    bool canMove;//save this pos if can move
};

#endif // VIEWMANAGER_H
