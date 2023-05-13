#include "Player.h"
#include "viewmanager.h"

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H




class GameManager
{
public:
    GameManager();
    Player White;
    Player Black;
    ViewManager board[8][8];
    int clickTimes;
    char selectChessPlayer;
    string selectChessType;
    int selectChessIndex;
    void showCanMove(int row, int col);
    void playerMove(int row, int col);
    bool ifGameOver();
    void computeTarget();
};

#endif // GAMEMANAGER_H
