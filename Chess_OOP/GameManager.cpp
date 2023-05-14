
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
            if(selectChessPlayer == 'w')
            {
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
