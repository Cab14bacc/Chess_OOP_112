#include <iostream>
#ifndef PAWN_H
#define PAWN_H

using namespace std;

class Pawn
{
public:
    char player;//while:w, black:b
    int x;//save pos x
    int y;//save pos y
    int index;//save index
    bool ifmove2Step = false;//save pawn if move two step
    bool inNextTurn = false;//save if this turn is after pawn move two step
    bool ifPromoting = false;//if pawn promoted
    string promotingType = "0";// if pawn have been promoted, save promoting type
};
#endif // PAWN_H
