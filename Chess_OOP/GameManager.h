#include "Player.h"
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H




class GameManager
{
public:
    char playerTurn;
    int clickTimes;
    GameManager();
    Player White;
    Player Black;
    void showCanMove(int row, int col);
    void playerMove(int row, int col);
    bool ifgameover();
};

#endif // GAMEMANAGER_H
