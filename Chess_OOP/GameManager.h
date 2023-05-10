#include "Player.h"
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H




class GameManager
{
public:
    char playerTurn;
    GameManager();
    Player White;
    Player Black;
    void startGame();
    void playerMove();
    bool ifgameover();
};

#endif // GAMEMANAGER_H
