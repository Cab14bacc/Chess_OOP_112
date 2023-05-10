#include "Player.h"
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H




class GameManager
{
public:
    GameManager();
    Player white;
    Player Black;
    void startGame();
    void whiteMove();
    void blackMove();
};

#endif // GAMEMANAGER_H
