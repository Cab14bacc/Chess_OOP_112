#include <vector>
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player
{
public:
    char player;//White:'w',Black:'b'
    vector<Pawn> pawns;//save pawns
    vector<Rook> rooks;//save rooks
    vector<Knight> knights;//save knights
    vector<Bishop> bishops;//save bishops
    vector<Queen> queens;//save queens
    King king;
};

#endif // PLAYER_H
