
#include "GameManager.h"

GameManager::GameManager()
{
    playerTurn = 'w';
    clickTimes = 1;
    White.setPlayer('w');
    Black.setPlayer('b');
    selectChessPlayer = '0';
    selectChessType = "0";
    selectChessIndex = 0;
}

void GameManager::showCanMove(int row, int col)
{

}

void GameManager::playerMove(int row, int col)
{

}

bool GameManager::ifGameOver()
{
    return true;
}

