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
    char selectChessPlayer;
    string selectChessType;
    int selectChessIndex;
    GameManager();
    void showCanMove(int row, int col);
    void playerMove(int row, int col);
    bool ifGameOver();
};

#endif // GAMEMANAGER_H
