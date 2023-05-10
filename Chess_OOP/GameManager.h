#include "Player.h"
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H




class GameManager
{
public:
    GameManager();
    Player White;
    Player Black;
    void startGame();
    void whiteMove();
    void blackMove();
    bool ifgameover();
};

#endif // GAMEMANAGER_H
