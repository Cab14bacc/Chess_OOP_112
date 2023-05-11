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
    Player();
    char player;
    void setPlayer(char play);
    vector<Pawn> pawns;
    vector<Rook> rooks;
    vector<Knight> knights;
    vector<Bishop> bishops;
    vector<Queen> queens;
    King king;
    void setNewGame();
};

#endif // PLAYER_H
