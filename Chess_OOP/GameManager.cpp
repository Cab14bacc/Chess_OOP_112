#include <iostream>
#include "GameManager.h"

using namespace std;

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
            if(selectChessPlayer == 'w')
            {
                if(row == 6)
                {
                    if(ifPosInBoard(row - 2, col) && board[row - 2][col].ifHavePiece == false)
                    {
                        board[row - 2][col].canMove = true;
                    }
                }

                if(ifPosInBoard(row - 1, col) && board[row - 1][col].ifHavePiece == false)
                {
                    board[row - 1][col].canMove = true;
                }

                if(ifPosInBoard(row - 1, col - 1) && boardChessCondition(row - 1, col - 1) == blackChess)
                {
                    board[row - 1][col - 1].canMove = true;
                }

                if(ifPosInBoard(row - 1, col + 1) && boardChessCondition(row - 1, col + 1) == blackChess)
                {
                    board[row - 1][col + 1].canMove = true;
                }
            }
            else//selectChessPlayer = 'b'
            {
                if(row == 1)
                {
                    if(ifPosInBoard(row + 2, col) && board[row + 2][col].ifHavePiece == false)
                    {
                        board[row + 2][col].canMove = true;
                    }
                }

                if(ifPosInBoard(row + 1, col) && board[row + 1][col].ifHavePiece == false)
                {
                    board[row + 1][col].canMove = true;
                }

                if(ifPosInBoard(row + 1, col - 1) && boardChessCondition(row + 1, col - 1) == whiteChess)
                {
                    board[row + 1][col - 1].canMove = true;
                }

                if(ifPosInBoard(row + 1, col + 1) && boardChessCondition(row + 1, col + 1) == whiteChess)
                {
                    board[row + 1][col + 1].canMove = true;
                }
            }
        }
        else if(selectChessType == "Rook")
        {
            //up
            for(int i = 1; i < 8;i++)
            {
                if(!ifPosInBoard(row + i, col))
                    break;

                if(boardChessCondition(row + i, col) == noChess)
                    board[row + i][col].canMove = true;
                else if(boardChessCondition(row + i, col) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col].canMove = true;
                        break;
                    }
                }
            }

            //down
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row - i, col))
                    break;

                if(boardChessCondition(row - i, col) == noChess)
                    board[row - i][col].canMove = true;
                else if(boardChessCondition(row - i, col) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col].canMove = true;
                        break;
                    }
                }
            }

            //right
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row, col + i))
                    break;

                if(boardChessCondition(row, col + i) == noChess)
                    board[row][col + i].canMove = true;
                else if(boardChessCondition(row, col + i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row][col + i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row][col + i].canMove = true;
                        break;
                    }
                }
            }

            //left
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row, col - i))
                    break;

                if(boardChessCondition(row, col - i) == noChess)
                    board[row][col - i].canMove = true;
                else if(boardChessCondition(row, col - i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row][col- i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row][col - i].canMove = true;
                        break;
                    }
                }
            }
        }
        else if(selectChessType == "Knight")
        {
            if(selectChessPlayer == 'w')
            {
                if(ifPosInBoard(row + 2, col + 1) && boardChessCondition(row + 2, col + 1) != whiteChess)
                    board[row + 2][col + 1].canMove = true;

                if(ifPosInBoard(row + 2, col - 1) && boardChessCondition(row + 2, col - 1) != whiteChess)
                    board[row + 2][col - 1].canMove = true;

                if(ifPosInBoard(row - 2, col + 1) && boardChessCondition(row - 2, col + 1) != whiteChess)
                    board[row - 2][col + 1].canMove = true;

                if(ifPosInBoard(row - 2, col - 1) && boardChessCondition(row - 2, col - 1) != whiteChess)
                    board[row - 2][col - 1].canMove = true;

                if(ifPosInBoard(row + 1, col + 2) && boardChessCondition(row + 1, col + 2) != whiteChess)
                    board[row + 1][col + 2].canMove = true;

                if(ifPosInBoard(row + 1, col - 2) && boardChessCondition(row + 1, col - 2) != whiteChess)
                    board[row + 1][col - 2].canMove = true;

                if(ifPosInBoard(row - 1, col + 2) && boardChessCondition(row - 1, col + 2) != whiteChess)
                    board[row - 1][col + 2].canMove = true;

                if(ifPosInBoard(row - 1, col - 2) && boardChessCondition(row - 1, col - 2) != whiteChess)
                    board[row - 1][col - 2].canMove = true;
            }
            else//selectChessPlayer == 'b'
            {
                if(ifPosInBoard(row + 2, col + 1) && boardChessCondition(row + 2, col + 1) != blackChess)
                    board[row + 2][col + 1].canMove = true;

                if(ifPosInBoard(row + 2, col - 1) && boardChessCondition(row + 2, col - 1) != blackChess)
                    board[row + 2][col - 1].canMove = true;

                if(ifPosInBoard(row - 2, col + 1) && boardChessCondition(row - 2, col + 1) != blackChess)
                    board[row - 2][col + 1].canMove = true;

                if(ifPosInBoard(row - 2, col - 1) && boardChessCondition(row - 2, col - 1) != blackChess)
                    board[row - 2][col - 1].canMove = true;

                if(ifPosInBoard(row + 1, col + 2) && boardChessCondition(row + 1, col + 2) != blackChess)
                    board[row + 1][col + 2].canMove = true;

                if(ifPosInBoard(row + 1, col - 2) && boardChessCondition(row + 1, col - 2) != blackChess)
                    board[row + 1][col - 2].canMove = true;

                if(ifPosInBoard(row - 1, col + 2) && boardChessCondition(row - 1, col + 2) != blackChess)
                    board[row - 1][col + 2].canMove = true;

                if(ifPosInBoard(row - 1, col - 2) && boardChessCondition(row - 1, col - 2) != blackChess)
                    board[row - 1][col - 2].canMove = true;
            }
        }
        else if(selectChessType == "Bishop")
        {
            //right up
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row + i, col + i))
                    break;

                if(boardChessCondition(row + i, col + i) == noChess)
                    board[row + i][col + i].canMove = true;
                else if(boardChessCondition(row + i, col + i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col + i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col + i].canMove = true;
                        break;
                    }
                }
            }

            //right down
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row - i, col + i))
                    break;

                if(boardChessCondition(row - i, col + i) == noChess)
                    board[row - i][col + i].canMove = true;
                else if(boardChessCondition(row - i, col + i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col + i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col + i].canMove = true;
                        break;
                    }
                }
            }

            //left up
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row + i, col - i))
                    break;

                if(boardChessCondition(row + i, col - i) == noChess)
                    board[row + i][col - i].canMove = true;
                else if(boardChessCondition(row + i, col - i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col - i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col - i].canMove = true;
                        break;
                    }
                }
            }

            //left down
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row - i, col - i))
                    break;

                if(boardChessCondition(row - i, col - i) == noChess)
                    board[row - i][col - i].canMove = true;
                else if(boardChessCondition(row - i, col - i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col- i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col - i].canMove = true;
                        break;
                    }
                }
            }
        }
        else if(selectChessType == "Queen")
        {
            //up
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row + i, col))
                    break;

                if(boardChessCondition(row + i, col) == noChess)
                    board[row + i][col].canMove = true;
                else if(boardChessCondition(row + i, col) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col].canMove = true;
                        break;
                    }
                }
            }

            //down
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row - i, col))
                    break;

                if(boardChessCondition(row - i, col) == noChess)
                    board[row - i][col].canMove = true;
                else if(boardChessCondition(row - i, col) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col].canMove = true;
                        break;
                    }
                }
            }

            //right
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row, col + i))
                    break;

                if(boardChessCondition(row, col + i) == noChess)
                    board[row][col + i].canMove = true;
                else if(boardChessCondition(row, col + i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row][col + i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row][col + i].canMove = true;
                        break;
                    }
                }
            }

            //left
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row, col - i))
                    break;

                if(boardChessCondition(row, col - i) == noChess)
                    board[row][col - i].canMove = true;
                else if(boardChessCondition(row, col - i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row][col- i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row][col - i].canMove = true;
                        break;
                    }
                }
            }

            //right up
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row + i, col + i))
                    break;

                if(boardChessCondition(row + i, col + i) == noChess)
                    board[row + i][col + i].canMove = true;
                else if(boardChessCondition(row + i, col + i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col + i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col + i].canMove = true;
                        break;
                    }
                }
            }

            //right down
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row - i, col + i))
                    break;

                if(boardChessCondition(row - i, col + i) == noChess)
                    board[row - i][col + i].canMove = true;
                else if(boardChessCondition(row - i, col + i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col + i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col + i].canMove = true;
                        break;
                    }
                }
            }

            //left up
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row + i, col - i))
                    break;

                if(boardChessCondition(row + i, col - i) == noChess)
                    board[row + i][col - i].canMove = true;
                else if(boardChessCondition(row + i, col - i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col - i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row + i][col - i].canMove = true;
                        break;
                    }
                }
            }

            //left down
            for(int i = 1;i<8;i++)
            {
                if(!ifPosInBoard(row - i, col - i))
                    break;

                if(boardChessCondition(row - i, col - i) == noChess)
                    board[row - i][col - i].canMove = true;
                else if(boardChessCondition(row - i, col - i) == whiteChess)
                {
                    if(selectChessPlayer == 'w')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col- i].canMove = true;
                        break;
                    }
                }
                else//boardChessCondition == blackChess
                {
                    if(selectChessPlayer == 'b')
                    {
                        break;
                    }
                    else
                    {
                        board[row - i][col - i].canMove = true;
                        break;
                    }
                }
            }
        }
        else if(selectChessType == "King")
        {
            if(selectChessPlayer == 'w')
            {
                //up
                if(ifPosInBoard(row + 1, col) && boardChessCondition(row + 1, col) != whiteChess && board[row + 1][col].bTarget == 0)
                    board[row + 1][col].canMove = true;

                //down
                if(ifPosInBoard(row - 1, col) && boardChessCondition(row - 1, col) != whiteChess && board[row - 1][col].bTarget == 0)
                    board[row - 1][col].canMove = true;

                //right
                if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) != whiteChess && board[row][col + 1].bTarget == 0)
                    board[row][col + 1].canMove = true;

                //left
                if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) != whiteChess && board[row][col - 1].bTarget == 0)
                    board[row][col - 1].canMove = true;

                //up right
                if(ifPosInBoard(row + 1, col + 1) && boardChessCondition(row + 1, col + 1) != whiteChess && board[row + 1][col + 1].bTarget == 0)
                    board[row + 1][col + 1].canMove = true;

                //up left
                if(ifPosInBoard(row + 1, col - 1) && boardChessCondition(row + 1, col - 1) != whiteChess && board[row + 1][col - 1].bTarget == 0)
                    board[row + 1][col - 1].canMove = true;

                //down right
                if(ifPosInBoard(row - 1, col + 1) && boardChessCondition(row - 1, col + 1) != whiteChess && board[row - 1][col + 1].bTarget == 0)
                    board[row - 1][col + 1].canMove = true;

                //down left
                if(ifPosInBoard(row - 1, col - 1) && boardChessCondition(row - 1, col - 1) != whiteChess && board[row - 1][col - 1].bTarget == 0)
                    board[row - 1][col - 1].canMove = true;
            }
            else//selectChessPlayer = 'b'
            {
                //up
                if(ifPosInBoard(row + 1, col) && boardChessCondition(row + 1, col) != blackChess && board[row + 1][col].bTarget == 0)
                    board[row + 1][col].canMove = true;

                //down
                if(ifPosInBoard(row - 1, col) && boardChessCondition(row - 1, col) != blackChess && board[row - 1][col].bTarget == 0)
                    board[row - 1][col].canMove = true;

                //right
                if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) != blackChess && board[row][col + 1].bTarget == 0)
                    board[row][col + 1].canMove = true;

                //left
                if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) != blackChess && board[row][col - 1].bTarget == 0)
                    board[row][col - 1].canMove = true;

                //up right
                if(ifPosInBoard(row + 1, col + 1) && boardChessCondition(row + 1, col + 1) != blackChess && board[row + 1][col + 1].bTarget == 0)
                    board[row + 1][col + 1].canMove = true;

                //up left
                if(ifPosInBoard(row + 1, col - 1) && boardChessCondition(row + 1, col - 1) != blackChess && board[row + 1][col - 1].bTarget == 0)
                    board[row + 1][col - 1].canMove = true;

                //down right
                if(ifPosInBoard(row - 1, col + 1) && boardChessCondition(row - 1, col + 1) != blackChess && board[row - 1][col + 1].bTarget == 0)
                    board[row - 1][col + 1].canMove = true;

                //down left
                if(ifPosInBoard(row - 1, col - 1) && boardChessCondition(row - 1, col - 1) != blackChess && board[row - 1][col - 1].bTarget == 0)
                    board[row - 1][col - 1].canMove = true;
            }
        }
    }
}

void GameManager::playerMove(int row, int col)
{
    if(board[row][col].canMove != true)
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                board[i][j].canMove = false;
            }
        }
        return;
    }

    if(board[row][col].ifHavePiece && board[row][col].player != selectChessPlayer)
    {
        eraseChessPiece(board[row][col].chessType,board[row][col].player,board[row][col].index);
    }

    if(selectChessPlayer == 'w')
    {
        if(selectChessType == "King")
        {
            if(board[row][col].chessType == "Rook" && board[row][col].player == 'w')
            {

                board[White.king.y][White.king.x].index = 0;
                board[White.king.y][White.king.x].chessType = "0";
                board[White.king.y][White.king.x].ifHavePiece = false;
                board[White.king.y][White.king.x].player = '0';

                if(White.king.x - White.rooks[board[row][col].index].x > 0)
                {
                    board[White.king.y][White.king.x - 2].chessType = selectChessType;
                    board[White.king.y][White.king.x - 2].index = selectChessIndex;
                    board[White.king.y][White.king.x - 2].ifHavePiece = true;
                    board[White.king.y][White.king.x - 2].player = selectChessPlayer;

                    board[White.king.y][White.king.x - 1].chessType = "Rook";
                    board[White.king.y][White.king.x - 1].index = board[row][col].index;
                    board[White.king.y][White.king.x - 1].ifHavePiece = true;
                    board[White.king.y][White.king.x - 1].player = selectChessPlayer;
                }
                else
                {

                    board[White.king.y][White.king.x + 2].chessType = selectChessType;
                    board[White.king.y][White.king.x + 2].index = selectChessIndex;
                    board[White.king.y][White.king.x + 2].ifHavePiece = true;
                    board[White.king.y][White.king.x + 2].player = selectChessPlayer;

                    board[White.king.y][White.king.x + 1].chessType = "Rook";
                    board[White.king.y][White.king.x + 1].index = board[row][col].index;
                    board[White.king.y][White.king.x + 1].ifHavePiece = true;
                    board[White.king.y][White.king.x + 1].player = selectChessPlayer;

                }
                board[row][col].chessType = "0";
                board[row][col].index = 0;
                board[row][col].ifHavePiece = false;
                board[row][col].player = '0';

            }
            else
            {
                board[White.king.y][White.king.x].ifHavePiece = false;//set original position ifHavePiece = false
                White.king.y = row;
                White.king.x = col;
                board[row][col].chessType = selectChessType;
                board[row][col].index = selectChessIndex;
                board[row][col].ifHavePiece = true;
                board[row][col].player = selectChessPlayer;
            }
            //452452

        }
        else
        {
            if(selectChessType == "Pawn")
            {
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].index = 0;
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].chessType = "0";
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].ifHavePiece = false;
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].player = '0';
                White.pawns[selectChessIndex].y = row;
                White.pawns[selectChessIndex].x = col;

            }
            else if(selectChessType == "Rook")
            {
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].index = 0;
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].chessType = "0";
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].ifHavePiece = false;
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].player = '0';
                White.rooks[selectChessIndex].y = row;
                White.rooks[selectChessIndex].x = col;
            }
            else if(selectChessType == "Bishop")
            {
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].index = 0;
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].chessType = "0";
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].ifHavePiece = false;
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].player = '0';
                White.bishops[selectChessIndex].y = row;
                White.bishops[selectChessIndex].x = col;
            }
            else if(selectChessType == "Knight")
            {

                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].index = 0;
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].chessType = "0";
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].ifHavePiece = false;
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].player = '0';
                White.knights[selectChessIndex].y = row;
                White.knights[selectChessIndex].x = col;
            }
            else if(selectChessType == "Queen")
            {
                board[White.queens[selectChessIndex].y][White.queens[selectChessIndex].x].index = 0;
                board[White.queens[selectChessIndex].y][White.queens[selectChessIndex].x].chessType = "0";
                board[White.queens[selectChessIndex].y][White.queens[selectChessIndex].x].ifHavePiece = false;
                board[White.queens[selectChessIndex].y][White.queens[selectChessIndex].x].player = '0';
                White.queens[selectChessIndex].y = row;
                White.queens[selectChessIndex].x = col;
            }
            board[row][col].chessType = selectChessType;
            board[row][col].index = selectChessIndex;
            board[row][col].ifHavePiece = true;
            board[row][col].player = selectChessPlayer;
        }

        playerTurn = 'b';//change playerTurn
    }
    else if(selectChessPlayer == 'b')
    {
        if(selectChessType == "King")
        {
            if(board[row][col].chessType == "Rook" && board[row][col].player == 'b')
            {

                board[Black.king.y][Black.king.x].index = 0;
                board[Black.king.y][Black.king.x].chessType = "0";
                board[Black.king.y][Black.king.x].ifHavePiece = false;
                board[Black.king.y][Black.king.x].player = '0';

                if(Black.king.x - Black.rooks[board[row][col].index].x > 0)
                {
                    board[Black.king.y][Black.king.x - 2].chessType = selectChessType;
                    board[Black.king.y][Black.king.x - 2].index = selectChessIndex;
                    board[Black.king.y][Black.king.x - 2].ifHavePiece = true;
                    board[Black.king.y][Black.king.x - 2].player = selectChessPlayer;

                    board[Black.king.y][Black.king.x - 1].chessType = "Rook";
                    board[Black.king.y][Black.king.x - 1].index = board[row][col].index;
                    board[Black.king.y][Black.king.x - 1].ifHavePiece = true;
                    board[Black.king.y][Black.king.x - 1].player = selectChessPlayer;
                }
                else
                {

                    board[Black.king.y][Black.king.x + 2].chessType = selectChessType;
                    board[Black.king.y][Black.king.x + 2].index = selectChessIndex;
                    board[Black.king.y][Black.king.x + 2].ifHavePiece = true;
                    board[Black.king.y][Black.king.x + 2].player = selectChessPlayer;

                    board[Black.king.y][Black.king.x + 1].chessType = "Rook";
                    board[Black.king.y][Black.king.x + 1].index = board[row][col].index;
                    board[Black.king.y][Black.king.x + 1].ifHavePiece = true;
                    board[Black.king.y][Black.king.x + 1].player = selectChessPlayer;

                }
                board[row][col].chessType = "0";
                board[row][col].index = 0;
                board[row][col].ifHavePiece = false;
                board[row][col].player = '0';

            }
            else
            {
                board[Black.king.y][Black.king.x].ifHavePiece = false;
                Black.king.y = row;
                Black.king.x = col;
                board[row][col].chessType = selectChessType;
                board[row][col].index = selectChessIndex;
                board[row][col].ifHavePiece = true;
                board[row][col].player = selectChessPlayer;
            }

        }
        else
        {
            if(selectChessType == "Pawn")
            {
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].index = 0;
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].chessType = "0";
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].ifHavePiece = false;
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].player = '0';
                Black.pawns[selectChessIndex].y = row;
                Black.pawns[selectChessIndex].x = col;
            }
            else if(selectChessType == "Rook")
            {
                board[Black.rooks[selectChessIndex].y][Black.rooks[selectChessIndex].x].index = 0;
                board[Black.rooks[selectChessIndex].y][Black.rooks[selectChessIndex].x].chessType = "0";
                board[Black.rooks[selectChessIndex].y][Black.rooks[selectChessIndex].x].ifHavePiece = false;
                board[Black.rooks[selectChessIndex].y][Black.rooks[selectChessIndex].x].player = '0';
                Black.rooks[selectChessIndex].y = row;
                Black.rooks[selectChessIndex].x = col;
            }
            else if(selectChessType == "Bishop")
            {
                board[Black.bishops[selectChessIndex].y][Black.bishops[selectChessIndex].x].index = 0;
                board[Black.bishops[selectChessIndex].y][Black.bishops[selectChessIndex].x].chessType = "0";
                board[Black.bishops[selectChessIndex].y][Black.bishops[selectChessIndex].x].ifHavePiece = false;
                board[Black.bishops[selectChessIndex].y][Black.bishops[selectChessIndex].x].player = '0';
                Black.bishops[selectChessIndex].y = row;
                Black.bishops[selectChessIndex].x = col;
            }
            else if(selectChessType == "Knight")
            {
                board[Black.knights[selectChessIndex].y][Black.knights[selectChessIndex].x].index = 0;
                board[Black.knights[selectChessIndex].y][Black.knights[selectChessIndex].x].chessType = "0";
                board[Black.knights[selectChessIndex].y][Black.knights[selectChessIndex].x].ifHavePiece = false;
                board[Black.knights[selectChessIndex].y][Black.knights[selectChessIndex].x].player = '0';
                Black.knights[selectChessIndex].y = row;
                Black.knights[selectChessIndex].x = col;
            }
            else if(selectChessType == "Queen")
            {
                board[Black.queens[selectChessIndex].y][Black.queens[selectChessIndex].x].index = 0;
                board[Black.queens[selectChessIndex].y][Black.queens[selectChessIndex].x].chessType = "0";
                board[Black.queens[selectChessIndex].y][Black.queens[selectChessIndex].x].ifHavePiece = false;
                board[Black.queens[selectChessIndex].y][Black.queens[selectChessIndex].x].player = '0';
                Black.queens[selectChessIndex].y = row;
                Black.queens[selectChessIndex].x = col;
            }
            board[row][col].chessType = selectChessType;
            board[row][col].index = selectChessIndex;
            board[row][col].ifHavePiece = true;
            board[row][col].player = selectChessPlayer;

        }

        playerTurn = 'w';//change playerTurn
    }
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            board[row][col].canMove = false;
        }
    }
}

void GameManager::eraseChessPiece(string chessType, char player,int index)
{
    if(player == 'w')
    {
        if(chessType == "Pawn")
        {
            White.pawns.erase(White.pawns.begin() + index);
        }
        else if(chessType == "Rook")
        {
            White.rooks.erase(White.rooks.begin() + index);
        }
        else if(chessType == "Bishop")
        {
            White.bishops.erase(White.bishops.begin() + index);
        }
        else if(chessType == "Knight")
        {
            White.knights.erase(White.knights.begin() + index);
        }
        else if(chessType == "Queen")
        {
            White.queens.erase(White.queens.begin() + index);
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

bool GameManager::ifGameOver()
{
    return true;
}

bool GameManager::ifPosInBoard(int row, int col)
{
    if(row >= 0 && row < 8 && col >= 0 && col < 8)
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

void check(int i,int j,ViewManager board[][8]);

void GameManager::computeTarget()
{
    for (int i = 0;i<8;i++)
    {
        for (int j = 0;j < 8;j++)
        {
            if (board[i][j].ifHavePiece)
            {
                check(i,j,board);
            }
        }
    }
}

void check(int i,int j,ViewManager board[][8])
{
    if(board[i][j].chessType == "Pawn")
    {
        if(board[i][j].player == 'w')
        {
            if (j+1<8&&i-1>0)
            {
                if (board[i-1][j+1].player!='w')
                {
                    board[i-1][j+1].wTarget++;
                }
            }
            if (j-1>0&&i-1>0)
            {
                if (board[i-1][j-1].player!='w')
                {
                    board[i-1][j-1].wTarget++;
                }
            }
        }
        else if(board[i][j].player == 'b')
        {
            if (j+1<8&&i+1<8)
            {
                if (board[i+1][j+1].player!='b')
                {
                    board[i+1][j+1].bTarget++;
                }
            }
            if (j-1>0&&i+1<8)
            {
                if (board[i+1][j-1].player!='b')
                {
                    board[i+1][j-1].bTarget++;
                }
            }
        }
    }
    else if(board[i][j].chessType == "Knight")
    {
        if(board[i][j].player == 'w')
        {
            if (j+2<8&&i+1<8)
            {
                if (board[i+1][j+2].player!='w')
                {
                    board[i+1][j+2].wTarget++;
                }
            }
            if (j+1<8&&i+2<8)
            {
                if (board[i+2][j+1].player!='w')
                {
                    board[i+2][j+1].wTarget++;
                }
            }
            if (j-2>0&&i+1<8)
            {
                if (board[i+1][j-2].player!='w')
                {
                    board[i+1][j-2].wTarget++;
                }
            }
            if (j-1>0&&i+2<8)
            {
                if (board[i+2][j-1].player!='w')
                {
                    board[i+2][j-1].wTarget++;
                }
            }
            if (j+2<8&&i-1>0)
            {
                if (board[i-1][j+2].player!='w')
                {
                    board[i-1][j+2].wTarget++;
                }
            }
            if (j+1<8&&i-2>0)
            {
                if (board[i-2][j+1].player!='w')
                {
                    board[i-2][j+1].wTarget++;
                }
            }
            if (j-2>0&&i-1>0)
            {
                if (board[i-1][j-2].player!='w')
                {
                    board[i-1][j-2].wTarget++;
                }
            }
            if (j-1>0&&i-2>0)
            {
                if (board[i-2][j-1].player!='w')
                {
                    board[i-2][j-1].wTarget++;
                }
            }
        }
        else if(board[i][j].player == 'b')
        {
            if (j+2<8&&i+1<8)
            {
                if (board[i+1][j+2].player!='b')
                {
                    board[i+1][j+2].bTarget++;
                }
            }
            if (j+1<8&&i+2<8)
            {
                if (board[i+2][j+1].player!='b')
                {
                    board[i+2][j+1].bTarget++;
                }
            }
            if (j-2>0&&i+1<8)
            {
                if (board[i+1][j-2].player!='b')
                {
                    board[i+1][j-2].bTarget++;
                }
            }
            if (j-1>0&&i+2<8)
            {
                if (board[i+2][j-1].player!='b')
                {
                    board[i+2][j-1].bTarget++;
                }
            }
            if (j+2<8&&i-1>0)
            {
                if (board[i-1][j+2].player!='b')
                {
                    board[i-1][j+2].bTarget++;
                }
            }
            if (j+1<8&&i-2>0)
            {
                if (board[i-2][j+1].player!='b')
                {
                    board[i-2][j+1].bTarget++;
                }
            }
            if (j-2>0&&i-1>0)
            {
                if (board[i-1][j-2].player!='b')
                {
                    board[i-1][j-2].bTarget++;
                }
            }
            if (j-1>0&&i-2>0)
            {
                if (board[i-2][j-1].player!='b')
                {
                    board[i-2][j-1].bTarget++;
                }
            }
        }
    }
    else if(board[i][j].chessType == "Rook")
    {
        if(board[i][j].player == 'w')
        {
            if(i+1<8)
            {
                for (int k = i+1;k<8;k++)
                {
                    if (board[k][j].player=='b')
                    {
                        board[k][j].wTarget++;
                        break;
                    }else if(board[k][j].player=='0')
                    {
                        board[k][j].wTarget++;
                    }
                    else if(board[k][j].player=='w')
                    {
                        break;
                    }
                }
            }
            if(i-1>=0)
            {
                for (int k = i-1;k>=0;k--)
                {
                    if (board[k][j].player=='b')
                    {
                        board[k][j].wTarget++;
                        break;
                    }else if(board[k][j].player=='0')
                    {
                        board[k][j].wTarget++;
                    }
                    else if(board[k][j].player=='w')
                    {
                        break;
                    }
                }
            }
            if(j+1<8)
            {
                for (int k = j+1;k<8;k++)
                {
                    if (board[i][k].player=='b')
                    {
                        board[i][k].wTarget++;
                        break;
                    }else if(board[i][k].player=='0')
                    {
                        board[i][k].wTarget++;
                    }
                    else if(board[i][k].player=='w')
                    {
                        break;
                    }
                }
            }
            if(j-1>=0)
            {
                for (int k = j-1;k>=0;k--)
                {
                    if (board[i][k].player=='b')
                    {
                        board[i][k].wTarget++;
                        break;
                    }else if(board[i][k].player=='0')
                    {
                        board[i][k].wTarget++;
                    }
                    else if(board[i][k].player=='w')
                    {
                        break;
                    }
                }
            }
        }
        else if(board[i][j].player == 'b')
        {
            if(i+1<8)
            {
                for (int k = i+1;k<8;k++)
                {
                    if (board[k][j].player=='w')
                    {
                        board[k][j].bTarget++;
                        break;
                    }else if(board[k][j].player=='0')
                    {
                        board[k][j].bTarget++;
                    }
                    else if(board[k][j].player=='b')
                    {
                        break;
                    }
                }
            }
            if(i-1>=0)
            {
                for (int k = i-1;k>=0;k--)
                {
                    if (board[k][j].player=='w')
                    {
                        board[k][j].bTarget++;
                        break;
                    }else if(board[k][j].player=='0')
                    {
                        board[k][j].bTarget++;
                    }
                    else if(board[k][j].player=='b')
                    {
                        break;
                    }
                }
            }
            if(j+1<8)
            {
                for (int k = j+1;k<8;k++)
                {
                    if (board[i][k].player=='w')
                    {
                        board[i][k].bTarget++;
                        break;
                    }else if(board[i][k].player=='0')
                    {
                        board[i][k].bTarget++;
                    }
                    else if(board[i][k].player=='b')
                    {
                        break;
                    }
                }
            }
            if(j-1>=0)
            {
                for (int k = j-1;k>=0;k--)
                {
                    if (board[i][k].player=='w')
                    {
                        board[i][k].bTarget++;
                        break;
                    }else if(board[i][k].player=='0')
                    {
                        board[i][k].bTarget++;
                    }
                    else if(board[i][k].player=='b')
                    {
                        break;
                    }
                }
            }
        }
    }
    else if(board[i][j].chessType == "Bishop")
    {
        if (board[i][j].player == 'w')
        {
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j+k<8)
                {
                    if (board[i+k][j+k].player=='b')
                    {
                        board[i+k][j+k].wTarget++;
                        break;
                    }
                    else if(board[i+k][j+k].player=='0')
                    {
                        board[i+k][j+k].wTarget++;
                    }
                    else if(board[i+k][j+k].player=='w')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j-k>=0)
                {
                    if (board[i+k][j-k].player=='b')
                    {
                        board[i+k][j-k].wTarget++;
                        break;
                    }
                    else if(board[i+k][j-k].player=='0')
                    {
                        board[i+k][j-k].wTarget++;
                    }
                    else if(board[i+k][j-k].player=='w')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j+k<8)
                {
                    if (board[i-k][j+k].player=='b')
                    {
                        board[i-k][j+k].wTarget++;
                        break;
                    }
                    else if(board[i-k][j+k].player=='0')
                    {
                        board[i-k][j+k].wTarget++;
                    }
                    else if(board[i-k][j+k].player=='w')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j-k>=0)
                {
                    if (board[i-k][j-k].player=='b')
                    {
                        board[i-k][j-k].wTarget++;
                        break;
                    }
                    else if(board[i-k][j-k].player=='0')
                    {
                        board[i-k][j-k].wTarget++;
                    }
                    else if(board[i-k][j-k].player=='w')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else if (board[i][j].player == 'b')
        {
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j+k<8)
                {
                    if (board[i+k][j+k].player=='w')
                    {
                        board[i+k][j+k].bTarget++;
                        break;
                    }
                    else if(board[i+k][j+k].player=='0')
                    {
                        board[i+k][j+k].bTarget++;
                    }
                    else if(board[i+k][j+k].player=='b')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j-k>=0)
                {
                    if (board[i+k][j-k].player=='w')
                    {
                        board[i+k][j-k].bTarget++;
                        break;
                    }
                    else if(board[i+k][j-k].player=='0')
                    {
                        board[i+k][j-k].bTarget++;
                    }
                    else if(board[i+k][j-k].player=='b')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j+k<8)
                {
                    if (board[i-k][j+k].player=='w')
                    {
                        board[i-k][j+k].bTarget++;
                        break;
                    }
                    else if(board[i-k][j+k].player=='0')
                    {
                        board[i-k][j+k].bTarget++;
                    }
                    else if(board[i-k][j+k].player=='b')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j-k>=0)
                {
                    if (board[i-k][j-k].player=='w')
                    {
                        board[i-k][j-k].bTarget++;
                        break;
                    }
                    else if(board[i-k][j-k].player=='0')
                    {
                        board[i-k][j-k].bTarget++;
                    }
                    else if(board[i-k][j-k].player=='b')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }
    else if(board[i][j].chessType == "Queen")
    {
        if (board[i][j].player == 'w')
        {
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j+k<8)
                {
                    if (board[i+k][j+k].player=='b')
                    {
                        board[i+k][j+k].wTarget++;
                        break;
                    }
                    else if(board[i+k][j+k].player=='0')
                    {
                        board[i+k][j+k].wTarget++;
                    }
                    else if(board[i+k][j+k].player=='w')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j-k>=0)
                {
                    if (board[i+k][j-k].player=='b')
                    {
                        board[i+k][j-k].wTarget++;
                        break;
                    }
                    else if(board[i+k][j-k].player=='0')
                    {
                        board[i+k][j-k].wTarget++;
                    }
                    else if(board[i+k][j-k].player=='w')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j+k<8)
                {
                    if (board[i-k][j+k].player=='b')
                    {
                        board[i-k][j+k].wTarget++;
                        break;
                    }
                    else if(board[i-k][j+k].player=='0')
                    {
                        board[i-k][j+k].wTarget++;
                    }
                    else if(board[i-k][j+k].player=='w')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j-k>=0)
                {
                    if (board[i-k][j-k].player=='b')
                    {
                        board[i-k][j-k].wTarget++;
                        break;
                    }
                    else if(board[i-k][j-k].player=='0')
                    {
                        board[i-k][j-k].wTarget++;
                    }
                    else if(board[i-k][j-k].player=='w')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            if(i+1<8)
            {
                for (int k = i+1;k<8;k++)
                {
                    if (board[k][j].player=='b')
                    {
                        board[k][j].wTarget++;
                        break;
                    }else if(board[k][j].player=='0')
                    {
                        board[k][j].wTarget++;
                    }
                    else if(board[k][j].player=='w')
                    {
                        break;
                    }
                }
            }
            if(i-1>=0)
            {
                for (int k = i-1;k>=0;k--)
                {
                    if (board[k][j].player=='b')
                    {
                        board[k][j].wTarget++;
                        break;
                    }else if(board[k][j].player=='0')
                    {
                        board[k][j].wTarget++;
                    }
                    else if(board[k][j].player=='w')
                    {
                        break;
                    }
                }
            }
            if(j+1<8)
            {
                for (int k = j+1;k<8;k++)
                {
                    if (board[i][k].player=='b')
                    {
                        board[i][k].wTarget++;
                        break;
                    }else if(board[i][k].player=='0')
                    {
                        board[i][k].wTarget++;
                    }
                    else if(board[i][k].player=='w')
                    {
                        break;
                    }
                }
            }
            if(j-1>=0)
            {
                for (int k = j-1;k>=0;k--)
                {
                    if (board[i][k].player=='b')
                    {
                        board[i][k].wTarget++;
                        break;
                    }else if(board[i][k].player=='0')
                    {
                        board[i][k].wTarget++;
                    }
                    else if(board[i][k].player=='w')
                    {
                        break;
                    }
                }
            }
        }
        else if (board[i][j].player == 'b')
        {
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j+k<8)
                {
                    if (board[i+k][j+k].player=='w')
                    {
                        board[i+k][j+k].bTarget++;
                        break;
                    }
                    else if(board[i+k][j+k].player=='0')
                    {
                        board[i+k][j+k].bTarget++;
                    }
                    else if(board[i+k][j+k].player=='b')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j-k>=0)
                {
                    if (board[i+k][j-k].player=='w')
                    {
                        board[i+k][j-k].bTarget++;
                        break;
                    }
                    else if(board[i+k][j-k].player=='0')
                    {
                        board[i+k][j-k].bTarget++;
                    }
                    else if(board[i+k][j-k].player=='b')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j+k<8)
                {
                    if (board[i-k][j+k].player=='w')
                    {
                        board[i-k][j+k].bTarget++;
                        break;
                    }
                    else if(board[i-k][j+k].player=='0')
                    {
                        board[i-k][j+k].bTarget++;
                    }
                    else if(board[i-k][j+k].player=='b')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j-k>=0)
                {
                    if (board[i-k][j-k].player=='w')
                    {
                        board[i-k][j-k].bTarget++;
                        break;
                    }
                    else if(board[i-k][j-k].player=='0')
                    {
                        board[i-k][j-k].bTarget++;
                    }
                    else if(board[i-k][j-k].player=='b')
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            if(i+1<8)
            {
                for (int k = i+1;k<8;k++)
                {
                    if (board[k][j].player=='w')
                    {
                        board[k][j].bTarget++;
                        break;
                    }else if(board[k][j].player=='0')
                    {
                        board[k][j].bTarget++;
                    }
                    else if(board[k][j].player=='b')
                    {
                        break;
                    }
                }
            }
            if(i-1>=0)
            {
                for (int k = i-1;k>=0;k--)
                {
                    if (board[k][j].player=='w')
                    {
                        board[k][j].bTarget++;
                        break;
                    }else if(board[k][j].player=='0')
                    {
                        board[k][j].bTarget++;
                    }
                    else if(board[k][j].player=='b')
                    {
                        break;
                    }
                }
            }
            if(j+1<8)
            {
                for (int k = j+1;k<8;k++)
                {
                    if (board[i][k].player=='w')
                    {
                        board[i][k].bTarget++;
                        break;
                    }else if(board[i][k].player=='0')
                    {
                        board[i][k].bTarget++;
                    }
                    else if(board[i][k].player=='b')
                    {
                        break;
                    }
                }
            }
            if(j-1>=0)
            {
                for (int k = j-1;k>=0;k--)
                {
                    if (board[i][k].player=='w')
                    {
                        board[i][k].bTarget++;
                        break;
                    }else if(board[i][k].player=='0')
                    {
                        board[i][k].bTarget++;
                    }
                    else if(board[i][k].player=='b')
                    {
                        break;
                    }
                }
            }
        }
    }
    else if(board[i][j].chessType == "King")
    {
        if (board[i][j].player == 'w')
        {
            if(i+1<8)
            {
                if(board[i+1][j].player != 'w')
                {
                    board[i+1][j].wTarget++;
                }
            }
            if(i-1>=0)
            {
                if(board[i-1][j].player != 'w')
                {
                    board[i-1][j].wTarget++;
                }
            }
            if(j+1<8)
            {
                if(board[i][j+1].player != 'w')
                {
                    board[i][j+1].wTarget++;
                }
            }
            if(j-1>=0)
            {
                if(board[i][j-1].player != 'w')
                {
                    board[i][j-1].wTarget++;
                }
            }
            if(i+1<8&&j+1<8)
            {
                if(board[i+1][j+1].player != 'w')
                {
                    board[i+1][j+1].wTarget++;
                }
            }
            if(i-1>=0&&j+1<8)
            {
                if(board[i-1][j+1].player != 'w')
                {
                    board[i-1][j+1].wTarget++;
                }
            }
            if(i+1<8&&j-1>=0)
            {
                if(board[i+1][j-1].player != 'w')
                {
                    board[i+1][j-1].wTarget++;
                }
            }
            if(i-1>=0&&j-1>=0)
            {
                if(board[i-1][j-1].player != 'w')
                {
                    board[i-1][j-1].wTarget++;
                }
            }
        }
        else if (board[i][j].player == 'b')
        {
            if(i+1<8)
            {
                if(board[i+1][j].player != 'b')
                {
                    board[i+1][j].wTarget++;
                }
            }
            if(i-1>=0)
            {
                if(board[i-1][j].player != 'b')
                {
                    board[i-1][j].wTarget++;
                }
            }
            if(j+1<8)
            {
                if(board[i][j+1].player != 'b')
                {
                    board[i][j+1].wTarget++;
                }
            }
            if(j-1>=0)
            {
                if(board[i][j-1].player != 'b')
                {
                    board[i][j-1].wTarget++;
                }
            }
            if(i+1<8&&j+1<8)
            {
                if(board[i+1][j+1].player != 'b')
                {
                    board[i+1][j+1].wTarget++;
                }
            }
            if(i-1>=0&&j+1<8)
            {
                if(board[i-1][j+1].player != 'b')
                {
                    board[i-1][j+1].wTarget++;
                }
            }
            if(i+1<8&&j-1>=0)
            {
                if(board[i+1][j-1].player != 'b')
                {
                    board[i+1][j-1].wTarget++;
                }
            }
            if(i-1>=0&&j-1>=0)
            {
                if(board[i-1][j-1].player != 'b')
                {
                    board[i-1][j-1].wTarget++;
                }
            }
        }
    }
}
