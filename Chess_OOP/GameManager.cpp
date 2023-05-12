
#include "GameManager.h"

GameManager::GameManager()
{
    White.setPlayer('w');
    Black.setPlayer('b');
    clickTimes = 1;
    selectChessPlayer = '0';
    selectChessType = "0";
    selectChessIndex = 0;
}

void GameManager::showCanMove(int row, int col)
{

}

void GameManager::playerMove(int row, int col)
{
    if(board[row][col].canMove != true)
    {
        return;
    }

    if(board[row][col].ifHavePiece)
    {
        eraseChessPiece(board[row][col].chessType,board[row][col].player,board[row][col].index);
    }

    if(selectChessPlayer == 'w')
    {
        if(selectChessType == "Pawn")
        {
            White.pawns[selectChessIndex].y = row;
            White.pawns[selectChessIndex].x = col;
        }
        else if(selectChessType == "Rook")
        {
            White.rooks[selectChessIndex].y = row;
            White.rooks[selectChessIndex].x = col;
        }
        else if(selectChessType == "Bishop")
        {
            White.bishops[selectChessIndex].y = row;
            White.bishops[selectChessIndex].x = col;
        }
        else if(selectChessType == "Knight")
        {
            White.knights[selectChessIndex].y = row;
            White.knights[selectChessIndex].x = col;
        }
        else if(selectChessType == "Queen")
        {
            White.queens[selectChessIndex].y = row;
            White.queens[selectChessIndex].x = col;
        }
        else if(selectChessType == "King")
        {
            White.king.y = row;
            White.king.x = col;
        }
    }
    else if(selectChessPlayer == 'b')
    {
        if(selectChessType == "Pawn")
        {
            Black.pawns[selectChessIndex].y = row;
            Black.pawns[selectChessIndex].x = col;
        }
        else if(selectChessType == "Rook")
        {
            Black.rooks[selectChessIndex].y = row;
            Black.rooks[selectChessIndex].x = col;
        }
        else if(selectChessType == "Bishop")
        {
            Black.bishops[selectChessIndex].y = row;
            Black.bishops[selectChessIndex].x = col;
        }
        else if(selectChessType == "Knight")
        {
            Black.knights[selectChessIndex].y = row;
            Black.knights[selectChessIndex].x = col;
        }
        else if(selectChessType == "Queen")
        {
            Black.queens[selectChessIndex].y = row;
            Black.queens[selectChessIndex].x = col;
        }
        else if(selectChessType == "King")
        {
            Black.king.y = row;
            Black.king.x = col;
        }

    }
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            board[row][col].canMove = false;
        }
    }
}

bool GameManager::ifGameOver()
{
    return true;
}

void GameManager::eraseChessPiece(string chessType, char player,int index)
{
    if(player == 'w')
    {

        if(chessType == "Pawn")
        {
            White.pawns.erase(White.pawns.begin()+index);
        }
        else if(chessType == "Rook")
        {
            White.rooks.erase(White.rooks.begin()+index);
        }
        else if(chessType == "Bishop")
        {
            White.bishops.erase(White.bishops.begin()+index);
        }
        else if(chessType == "Knight")
        {
            White.knights.erase(White.knights.begin()+index);
        }
        else if(chessType == "Queen")
        {
            White.queens.erase(White.queens.begin()+index);
        }
//        else if(chessType == "King")
//        {

//        }

    }
    else if(player == 'b')
    {
        if(chessType == "Pawn")
        {
            Black.pawns.erase(Black.pawns.begin()+index);
        }
        else if(chessType == "Rook")
        {
            Black.rooks.erase(Black.rooks.begin()+index);
        }
        else if(chessType == "Bishop")
        {
            Black.bishops.erase(Black.bishops.begin()+index);
        }
        else if(chessType == "Knight")
        {
            Black.knights.erase(Black.knights.begin()+index);
        }
        else if(chessType == "Queen")
        {
            Black.queens.erase(Black.queens.begin()+index);
        }
//        else if(chessType == "King")
//        {
//
//        }
    }

}
