#include "Player.h"
#include "Board.h"
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H




class GameManager
{
public:
    char playerTurn;
    int clickTimes;
    Player White;
    Player Black;
    Board board[8][8];
    GameManager();
    void showCanMove(int row, int col);
    void playerMove(int row, int col);
    bool ifgameover();
};

#endif // GAMEMANAGER_H
