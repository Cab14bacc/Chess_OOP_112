#include "Player.h"
#include "viewmanager.h"

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#define whiteChess 1
#define blackChess 2
#define noChess 3


class GameManager
{
public:
    GameManager();
    Player White;
    Player Black;
    ViewManager board[8][8];
    int clickTimes;
    char playerTurn;
    char selectChessPlayer;
    string selectChessType;
    int selectChessIndex;
    void showCanMove(int row, int col);
    void playerMove(int row, int col);
    bool ifGameOver();
    bool ifPosInBoard(int row, int col);
    int boardChessCondition(int row, int col);//return 1:white chess、2:black、3:no chess on the board
};

#endif // GAMEMANAGER_H
