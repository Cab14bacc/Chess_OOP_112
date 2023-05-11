#include "Player.h"
<<<<<<< HEAD
#include "viewmanager.h"
=======
>>>>>>> 31dbd3d3940833b5f08818f48a2476d4e8aca63c
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H




class GameManager
{
public:
    GameManager();
    Player White;
    Player Black;
<<<<<<< HEAD
    ViewManager board[8][8];
    char selectChessPlayer;
    string selectChessType;
    int selectChessIndex;
    GameManager();
    void showCanMove(int row, int col);
    void playerMove(int row, int col);
    bool ifGameOver();
=======
    void startGame();
    void whiteMove();
    void blackMove();
    bool ifgameover();
>>>>>>> 31dbd3d3940833b5f08818f48a2476d4e8aca63c
};

#endif // GAMEMANAGER_H
