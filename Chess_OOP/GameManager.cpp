
#include "GameManager.h"

GameManager::GameManager()
{
    White.setPlayer('w');
    Black.setPlayer('b');
}

void GameManager::startGame()
{
    while(ifgameover())
    {
        whiteMove();
        blackMove();
    }
}

void GameManager::whiteMove()
{

}

void GameManager::blackMove()
{

}

bool GameManager::ifgameover()
{
    return true;
}

