
#include "GameManager.h"

GameManager::GameManager()
{
    White.setPlayer('w');
    Black.setPlayer('b');
    clickTimes = 1;
    playerTurn = 'w';
    selectChessPlayer = '0';
    selectChessType = "0";
    selectChessIndex = 0;
}

void GameManager::showCanMove(int row, int col)
{
    if(this->board[row][col].ifHavePiece && playerTurn == this->board[row][col].player)
    {
        clickTimes = 2;
        selectChessPlayer = this->board[row][col].player;
        selectChessType = this->board[row][col].chessType;
        selectChessIndex = this->board[row][col].index;

        if(selectChessType == "Pawn")
        {

        }
        else if(selectChessType == "Rook")
        {

        }
        else if(selectChessType == "Knight")
        {

        }
        else if(selectChessType == "Bishop")
        {

        }
        else if(selectChessType == "Queen")
        {

        }
        else if(selectChessType == "King")
        {

        }
    }
}

void GameManager::playerMove(int row, int col)
{

}

bool GameManager::ifGameOver()
{
    return true;
}

bool GameManager::ifPosInBoard(int row, int col)
{
    if(row > 0 && row < 8 && col > 0 && col < 8)
    {
        return true;
    }

    return false;
}

int GameManager::boardChessCondition(int row, int col)
{
    if(!board[row][col].ifHavePiece)
    {
        return noChess;
    }
    else if(board[row][col].player == 'w')
    {
        return whiteChess;
    }
    else if(board[row][col].player == 'b')
    {
        return blackChess;
    }
}
