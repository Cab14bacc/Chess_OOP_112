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
    vector<Pawn> pawns;
    vector<Rook> rooks;
    vector<Knight> knights;
    vector<Bishop> bishops;
    vector<Queen> queens;
    King king;
};

#endif // PLAYER_H
