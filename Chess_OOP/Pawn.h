#include <iostream>
#ifndef PAWN_H
#define PAWN_H

using namespace std;

class Pawn
{
public:
    char player;//while:w, black:b
    int x;
    int y;
    int index;
    bool ifmove2Step = false;
    bool inNextTurn = false;
    bool ifPromoting = false;
    string promotingType = "0";
};
#endif // PAWN_H
