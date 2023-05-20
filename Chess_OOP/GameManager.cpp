#include <iostream>
#include "GameManager.h"


using namespace std;

//intent: initialize Game
//pre: none
//post: game initialized
GameManager::GameManager()
{
    //intialized how many of each chess piece there is
    wPawn = 8;
    wRook = 2;
    wKnight = 2;
    wBishop = 2;
    wQueen = 1;
    bPawn = 8;
    bRook = 2;
    bKnight = 2;
    bBishop = 2;
    bQueen = 1;

    //how many times has a move eaten any piece
    noEat = 0;

    fen = "";

    //if white or black can move
    ifWhiteCanMove = true;
    ifBlackCanMove = true;
    //if game tied
    ifDraw = false;

    //current step count
    curStep = 0;
    //init characters
    White.player = 'w';
    Black.player = 'b';
    clickTimes = 1;
    playerTurn = '0';
    selectChessPlayer = '0';
    selectChessType = "0";
    selectChessIndex = 0;
}

//intent: calculate what are the valid places a piece at [row][col] can move
//pre: game intialized
//post: valid places are stored
void GameManager::showCanMove(int row, int col)
{
    for(int i = 0;i < 8; i++)
    {
        for(int j = 0; j < 8 ;j++)
        {
            board[i][j].canMove = false;
        }
    }

    //if this block has piece and if the chess piece corresponds to the current player's turn
    if(this->board[row][col].ifHavePiece && playerTurn == this->board[row][col].player)
    {
        //set click times
        clickTimes = 2;

        selectChessPlayer = this->board[row][col].player;
        selectChessType = this->board[row][col].chessType;
        selectChessIndex = this->board[row][col].index;

        //if pawn
        if(selectChessType == "Pawn")
        {
            //if white piece selected
            if(selectChessPlayer == 'w')
            {
                //first step
                if(row == 6)
                {
                    if(ifPosInBoard(row - 2, col) && board[row - 2][col].ifHavePiece == false && board[row - 1][col].ifHavePiece == false)
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

                //En passant
                if(row == 3)
                {
                    //left En passant
                    if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) == blackChess && board[row][col - 1].chessType == "Pawn")
                    {
                        if(Black.pawns[board[row][col - 1].index].ifmove2Step == true && Black.pawns[board[row][col - 1].index].inNextTurn == true)
                        {
                            board[row][col - 1].canMove = true;
                        }
                    }

                    //right En passant
                    if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) == blackChess && board[row][col + 1].chessType == "Pawn")
                    {
                        if(Black.pawns[board[row][col + 1].index].ifmove2Step == true && Black.pawns[board[row][col + 1].index].inNextTurn == true)
                        {
                            board[row][col + 1].canMove = true;
                        }
                    }
                }
            }
            else//selectChessPlayer = 'b'
            {
                //first step
                if(row == 1)
                {
                    if(ifPosInBoard(row + 2, col) && board[row + 2][col].ifHavePiece == false && board[row + 1][col].ifHavePiece == false)
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

                //En passant
                if(row == 4)
                {
                    //left En passant
                    if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) == whiteChess && board[row][col - 1].chessType == "Pawn")
                    {
                        if(White.pawns[board[row][col - 1].index].ifmove2Step == true && White.pawns[board[row][col - 1].index].inNextTurn == true)
                        {
                            board[row][col - 1].canMove = true;
                        }
                    }

                    //right En passant
                    if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) == whiteChess && board[row][col + 1].chessType == "Pawn")
                    {
                        if(White.pawns[board[row][col + 1].index].ifmove2Step == true && White.pawns[board[row][col + 1].index].inNextTurn == true)
                        {
                            board[row][col + 1].canMove = true;
                        }
                    }
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

                //left castle
                if(White.king.ifMove == false && White.rooks[board[7][0].index].ifMove == false && board[7][0].chessType == "Rook" && board[7][0].player == 'w')
                {
                    if(board[7][1].ifHavePiece == false && board[7][2].ifHavePiece == false && board[7][3].ifHavePiece == false)
                    {
                        if(board[7][4].bTarget == 0 && board[7][1].bTarget == 0 && board[7][2].bTarget == 0 && board[7][3].bTarget == 0)
                        {
                            board[7][0].canMove = true;
                        }
                    }
                }

                //right castle
                if(White.king.ifMove == false && White.rooks[board[7][7].index].ifMove == false && board[7][7].chessType == "Rook" && board[7][7].player == 'w')
                {
                    if(board[7][5].ifHavePiece == false && board[7][6].ifHavePiece == false)
                    {
                        if(board[7][4].bTarget == 0 && board[7][5].bTarget == 0 && board[7][6].bTarget == 0)
                        {
                            board[7][7].canMove = true;
                        }
                    }
                }
            }
            else//selectChessPlayer = 'b'
            {
                //up
                if(ifPosInBoard(row + 1, col) && boardChessCondition(row + 1, col) != blackChess && board[row + 1][col].wTarget == 0)
                    board[row + 1][col].canMove = true;

                //down
                if(ifPosInBoard(row - 1, col) && boardChessCondition(row - 1, col) != blackChess && board[row - 1][col].wTarget == 0)
                    board[row - 1][col].canMove = true;

                //right
                if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) != blackChess && board[row][col + 1].wTarget == 0)
                    board[row][col + 1].canMove = true;

                //left
                if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) != blackChess && board[row][col - 1].wTarget == 0)
                    board[row][col - 1].canMove = true;

                //up right
                if(ifPosInBoard(row + 1, col + 1) && boardChessCondition(row + 1, col + 1) != blackChess && board[row + 1][col + 1].wTarget == 0)
                    board[row + 1][col + 1].canMove = true;

                //up left
                if(ifPosInBoard(row + 1, col - 1) && boardChessCondition(row + 1, col - 1) != blackChess && board[row + 1][col - 1].wTarget == 0)
                    board[row + 1][col - 1].canMove = true;

                //down right
                if(ifPosInBoard(row - 1, col + 1) && boardChessCondition(row - 1, col + 1) != blackChess && board[row - 1][col + 1].wTarget == 0)
                    board[row - 1][col + 1].canMove = true;

                //down left
                if(ifPosInBoard(row - 1, col - 1) && boardChessCondition(row - 1, col - 1) != blackChess && board[row - 1][col - 1].wTarget == 0)
                    board[row - 1][col - 1].canMove = true;

                //left castle
                if(Black.king.ifMove == false && Black.rooks[board[0][0].index].ifMove == false && board[0][0].chessType == "Rook" && board[0][0].player == 'b')
                {
                    if(board[0][1].ifHavePiece == false && board[0][2].ifHavePiece == false && board[0][3].ifHavePiece == false)
                    {
                        if(board[0][4].wTarget == 0 && board[0][1].wTarget == 0 && board[0][2].wTarget == 0 && board[0][3].wTarget == 0)
                        {
                            board[0][0].canMove = true;
                        }
                    }
                }

                //right castle
                if(Black.king.ifMove == false && Black.rooks[board[0][7].index].ifMove == false && board[0][7].chessType == "Rook" && board[0][7].player == 'b')
                {
                    if(board[0][5].ifHavePiece == false && board[0][6].ifHavePiece == false)
                    {
                        if(board[0][4].wTarget == 0 && board[0][5].wTarget == 0 && board[0][6].wTarget == 0)
                        {
                            board[0][7].canMove = true;
                        }
                    }
                }
            }
        }
    }
}

//intent: player move
//pre: showCanMove() is called
//post: player moved
void GameManager::playerMove(int row, int col)
{

    //reset canMove variables
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

    //increment no eat
    noEat++;

    for(int i = 0;i<White.pawns.size();i++)
    {
        White.pawns[i].inNextTurn = false;
    }

    for(int i = 0;i<Black.pawns.size();i++)
    {
        Black.pawns[i].inNextTurn = false;
    }

    //if there is a piece at the square clicked, meaning player takes will take that piece with this move
    //erase that piece if true
    if(board[row][col].ifHavePiece)
    {
        noEat = 0;
    }

    curMove.chessPlayer = selectChessPlayer;
    curMove.chessType = selectChessType;

    //check which chess is selected and check the chess piece on the square clicked
    if(selectChessPlayer == 'w')
    {
        if(selectChessType == "King")
        {
            curMove.originalPos[0] = White.king.y;
            curMove.originalPos[1] = White.king.x;

            //if castle
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

                    White.rooks[board[row][col].index].x = White.king.x - 1;
                    White.king.x = White.king.x - 2;
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

                    White.rooks[board[row][col].index].x = White.king.x + 1;
                    White.king.x = White.king.x + 2;
                }
                board[row][col].chessType = "0";
                board[row][col].index = 0;
                board[row][col].ifHavePiece = false;
                board[row][col].player = '0';

            }
            else // if not castle
            {
                board[White.king.y][White.king.x].index = 0;
                board[White.king.y][White.king.x].chessType = "0";
                board[White.king.y][White.king.x].player = '0';
                board[White.king.y][White.king.x].ifHavePiece = false;//set original position ifHavePiece = false
                White.king.y = row;
                White.king.x = col;
                board[row][col].chessType = selectChessType;
                board[row][col].index = selectChessIndex;
                board[row][col].ifHavePiece = true;
                board[row][col].player = selectChessPlayer;
            }

            curMove.afterPos[0] = White.king.y;
            curMove.afterPos[1] = White.king.x;
            White.king.ifMove = true;
        }
        else if(selectChessType == "Pawn")
        {
            White.pawns[selectChessIndex].ifPromoting = false;
            curMove.originalPos[0] = White.pawns[selectChessIndex].y;
            curMove.originalPos[1] = White.pawns[selectChessIndex].x;

            //en passant
            if(board[row][col].chessType == "Pawn" && row == White.pawns[selectChessIndex].y)
            {
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].index = 0;
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].chessType = "0";
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].ifHavePiece = false;
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].player = '0';

                White.pawns[selectChessIndex].y = row - 1;
                White.pawns[selectChessIndex].x = col;

                board[row - 1][col].chessType = selectChessType;
                board[row - 1][col].index = selectChessIndex;
                board[row - 1][col].ifHavePiece = true;
                board[row - 1][col].player = selectChessPlayer;

                board[row][col].chessType = "0";
                board[row][col].index = 0;
                board[row][col].ifHavePiece = false;
                board[row][col].player = '0';
            }
            else // not en passant
            {
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].index = 0;
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].chessType = "0";
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].ifHavePiece = false;
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].player = '0';

                if(White.pawns[selectChessIndex].y - row == 2)
                {
                    White.pawns[selectChessIndex].ifmove2Step = true;
                    White.pawns[selectChessIndex].inNextTurn = true;
                }
                else
                {
                    White.pawns[selectChessIndex].ifmove2Step = false;
                }

                White.pawns[selectChessIndex].y = row;
                White.pawns[selectChessIndex].x = col;

                board[row][col].chessType = selectChessType;
                board[row][col].index = selectChessIndex;
                board[row][col].ifHavePiece = true;
                board[row][col].player = selectChessPlayer;
            }

            curMove.afterPos[0] = White.pawns[selectChessIndex].y;
            curMove.afterPos[1] = White.pawns[selectChessIndex].x;
        }
        else //selected chess piece is not king or pawn, all normal moves
        {
            if(selectChessType == "Rook")
            {
                curMove.originalPos[0] = White.rooks[selectChessIndex].y;
                curMove.originalPos[1] = White.rooks[selectChessIndex].x;
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].index = 0;
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].chessType = "0";
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].ifHavePiece = false;
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].player = '0';
                White.rooks[selectChessIndex].y = row;
                White.rooks[selectChessIndex].x = col;
                curMove.afterPos[0] = White.rooks[selectChessIndex].y;
                curMove.afterPos[1] = White.rooks[selectChessIndex].x;
                White.rooks[selectChessIndex].ifMove = true;
            }
            else if(selectChessType == "Bishop")
            {
                curMove.originalPos[0] = White.bishops[selectChessIndex].y;
                curMove.originalPos[1] = White.bishops[selectChessIndex].x;
                curMove.afterPos[0] = row;
                curMove.afterPos[1] = col;
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].index = 0;
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].chessType = "0";
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].ifHavePiece = false;
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].player = '0';
                White.bishops[selectChessIndex].y = row;
                White.bishops[selectChessIndex].x = col;
            }
            else if(selectChessType == "Knight")
            {
                curMove.originalPos[0] = White.knights[selectChessIndex].y;
                curMove.originalPos[1] = White.knights[selectChessIndex].x;
                curMove.afterPos[0] = row;
                curMove.afterPos[1] = col;
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].index = 0;
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].chessType = "0";
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].ifHavePiece = false;
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].player = '0';
                White.knights[selectChessIndex].y = row;
                White.knights[selectChessIndex].x = col;
            }
            else if(selectChessType == "Queen")
            {
                curMove.originalPos[0] = White.queens[selectChessIndex].y;
                curMove.originalPos[1] = White.queens[selectChessIndex].x;
                curMove.afterPos[0] = row;
                curMove.afterPos[1] = col;
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
    else if(selectChessPlayer == 'b') // same as white, but mirrored
    {
        if(selectChessType == "King")
        {
            curMove.originalPos[0] = Black.king.y;
            curMove.originalPos[1] = Black.king.x;

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

                    Black.rooks[board[row][col].index].x = Black.king.x - 1;
                    Black.king.x = Black.king.x - 2;
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

                    Black.rooks[board[row][col].index].x = Black.king.x + 1;
                    Black.king.x = Black.king.x + 2;
                }
                board[row][col].chessType = "0";
                board[row][col].index = 0;
                board[row][col].ifHavePiece = false;
                board[row][col].player = '0';

            }
            else
            {
                board[Black.king.y][Black.king.x].index = 0;
                board[Black.king.y][Black.king.x].chessType = "0";
                board[Black.king.y][Black.king.x].player = '0';
                board[Black.king.y][Black.king.x].ifHavePiece = false;
                Black.king.y = row;
                Black.king.x = col;
                board[row][col].chessType = selectChessType;
                board[row][col].index = selectChessIndex;
                board[row][col].ifHavePiece = true;
                board[row][col].player = selectChessPlayer;
            }

            curMove.afterPos[0] = Black.king.y;
            curMove.afterPos[1] = Black.king.x;
            Black.king.ifMove = true;
        }
        else if(selectChessType == "Pawn")
        {
            Black.pawns[selectChessIndex].ifPromoting = false;
            curMove.originalPos[0] = Black.pawns[selectChessIndex].y;
            curMove.originalPos[1] = Black.pawns[selectChessIndex].x;

            if(board[row][col].chessType == "Pawn" && row == Black.pawns[selectChessIndex].y)
            {
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].index = 0;
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].chessType = "0";
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].ifHavePiece = false;
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].player = '0';

                Black.pawns[selectChessIndex].y = row + 1;
                Black.pawns[selectChessIndex].x = col;

                board[row + 1][col].chessType = selectChessType;
                board[row + 1][col].index = selectChessIndex;
                board[row + 1][col].ifHavePiece = true;
                board[row + 1][col].player = selectChessPlayer;

                board[row][col].chessType = "0";
                board[row][col].index = 0;
                board[row][col].ifHavePiece = false;
                board[row][col].player = '0';

            }
            else
            {
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].index = 0;
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].chessType = "0";
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].ifHavePiece = false;
                board[Black.pawns[selectChessIndex].y][Black.pawns[selectChessIndex].x].player = '0';

                if(row - Black.pawns[selectChessIndex].y == 2)
                {
                    Black.pawns[selectChessIndex].ifmove2Step = true;
                    Black.pawns[selectChessIndex].inNextTurn = true;
                }
                else
                {
                    Black.pawns[selectChessIndex].ifmove2Step = false;
                }

                Black.pawns[selectChessIndex].y = row;
                Black.pawns[selectChessIndex].x = col;

                board[row][col].chessType = selectChessType;
                board[row][col].index = selectChessIndex;
                board[row][col].ifHavePiece = true;
                board[row][col].player = selectChessPlayer;
            }

            curMove.afterPos[0] = Black.pawns[selectChessIndex].y;
            curMove.afterPos[1] = Black.pawns[selectChessIndex].x;
        }
        else
        {
            if(selectChessType == "Rook")
            {
                curMove.originalPos[0] = Black.rooks[selectChessIndex].y;
                curMove.originalPos[1] = Black.rooks[selectChessIndex].x;
                curMove.afterPos[0] = row;
                curMove.afterPos[1] = col;
                board[Black.rooks[selectChessIndex].y][Black.rooks[selectChessIndex].x].index = 0;
                board[Black.rooks[selectChessIndex].y][Black.rooks[selectChessIndex].x].chessType = "0";
                board[Black.rooks[selectChessIndex].y][Black.rooks[selectChessIndex].x].ifHavePiece = false;
                board[Black.rooks[selectChessIndex].y][Black.rooks[selectChessIndex].x].player = '0';
                Black.rooks[selectChessIndex].y = row;
                Black.rooks[selectChessIndex].x = col;
                Black.rooks[selectChessIndex].ifMove = true;
            }
            else if(selectChessType == "Bishop")
            {
                curMove.originalPos[0] = Black.bishops[selectChessIndex].y;
                curMove.originalPos[1] = Black.bishops[selectChessIndex].x;
                curMove.afterPos[0] = row;
                curMove.afterPos[1] = col;
                board[Black.bishops[selectChessIndex].y][Black.bishops[selectChessIndex].x].index = 0;
                board[Black.bishops[selectChessIndex].y][Black.bishops[selectChessIndex].x].chessType = "0";
                board[Black.bishops[selectChessIndex].y][Black.bishops[selectChessIndex].x].ifHavePiece = false;
                board[Black.bishops[selectChessIndex].y][Black.bishops[selectChessIndex].x].player = '0';
                Black.bishops[selectChessIndex].y = row;
                Black.bishops[selectChessIndex].x = col;
            }
            else if(selectChessType == "Knight")
            {
                curMove.originalPos[0] = Black.knights[selectChessIndex].y;
                curMove.originalPos[1] = Black.knights[selectChessIndex].x;
                curMove.afterPos[0] = row;
                curMove.afterPos[1] = col;
                board[Black.knights[selectChessIndex].y][Black.knights[selectChessIndex].x].index = 0;
                board[Black.knights[selectChessIndex].y][Black.knights[selectChessIndex].x].chessType = "0";
                board[Black.knights[selectChessIndex].y][Black.knights[selectChessIndex].x].ifHavePiece = false;
                board[Black.knights[selectChessIndex].y][Black.knights[selectChessIndex].x].player = '0';
                Black.knights[selectChessIndex].y = row;
                Black.knights[selectChessIndex].x = col;
            }
            else if(selectChessType == "Queen")
            {
                curMove.originalPos[0] = Black.queens[selectChessIndex].y;
                curMove.originalPos[1] = Black.queens[selectChessIndex].x;
                curMove.afterPos[0] = row;
                curMove.afterPos[1] = col;
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


    computeChessNumber(); // compute number of each chess piece on baord
    computeTarget(); //compute for each squares, how many white pieces and how many black pieces can move to or attack this square
    recordCurBoard(); // record the board after each move
    curStep++; // increment current step( current round )
    steps.resize(curStep + 1);// resize the vector that stores the previous boards
    steps[curStep] = curBoard; // store the board into this vector
    transBoardToFen(); // transform board to fen encoding
    fens.resize(curStep + 1);// resize the vector that stores fen-encoded board
    fens[curStep] = fen; // store the fen-encoded board into vector
    moves.resize(curStep + 1);//resize the vector that stores moves
    moves[curStep] = curMove;// store the current move into vector
    IfBoardRepeat3Times(fen); // if same board repeat 3 times
    ifWhiteCanMove = false; // reset if white can move
    ifBlackCanMove = false;// reset if black can move
    judgeIfPlayerCanMove(playerTurn);// rejudge if white or black can move

    //check if insufficient chess pieces left
    if(wPawn == 0 && wRook == 0 && wKnight == 0 && wBishop == 0 && wQueen == 0)
        ifInsufficientChess();

    if(bPawn == 0 && bRook == 0 && bKnight == 0 && bBishop == 0 && bQueen == 0)
        ifInsufficientChess();
}

//intent: check if coordinate are in bound
//pre: none
//post: return if coordinate are in bound
bool GameManager::ifPosInBoard(int row, int col)
{
    if(row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        return true;
    }

    return false;
}

//intent: return whether this square has no chess piece, or white chess piece or black chess piece
//pre: none
//post: return current state of one of the 3 situations
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

//intent: for a chess piece on the specified square, calculate
//and increment the number of possible targeting chesspieces on all the possible paths of this specified chess piece
//pre: board is initialized
//post: the possible destinations are stored
int check(int i,int j,ViewManager board[][8])
{
    int kingAttack = 0;
    //if the input board's piece type is Pawn.
    if(board[i][j].chessType == "Pawn")
    {
        //check which side it is.
        if(board[i][j].player == 'w')
        {
            //check up left and up right
            if (j+1<8&&i-1>=0)
            {
                //if the destination is not teammate
                if (board[i-1][j+1].player!='w')
                {
                    board[i-1][j+1].wTarget++;
                    //check if attack king
                    if (board[i-1][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-1>=0&&i-1>=0)
            {
                //if the destination is not teammate
                if (board[i-1][j-1].player!='w')
                {
                    board[i-1][j-1].wTarget++;
                    //check if attack king
                    if (board[i-1][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
        }
        else if(board[i][j].player == 'b')
        {
            //check up left and up right
            if (j+1<8&&i+1<8)
            {
                //if the destination is not teammate
                if (board[i+1][j+1].player!='b')
                {
                    board[i+1][j+1].bTarget++;
                    //check if attack king
                    if (board[i+1][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-1>=0&&i+1<8)
            {
                //if the destination is not teammate
                if (board[i+1][j-1].player!='b')
                {
                    board[i+1][j-1].bTarget++;
                    //check if attack king
                    if (board[i+1][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
        }
    }
    //if the input board's piece type is Knight.
    else if(board[i][j].chessType == "Knight")
    {
        //check which side it is.
        if(board[i][j].player == 'w')
        {
            //check the eight directions that knight can move to.
            if (j+2<8&&i+1<8)
            {
                //if the destination is not teammate
                if (board[i+1][j+2].player!='w')
                {
                    board[i+1][j+2].wTarget++;
                    //check if attack king
                    if (board[i+1][j+2].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j+1<8&&i+2<8)
            {
                //if the destination is not teammate
                if (board[i+2][j+1].player!='w')
                {
                    board[i+2][j+1].wTarget++;
                    //check if attack king
                    if (board[i+2][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-2>=0&&i+1<8)
            {
                //if the destination is not teammate
                if (board[i+1][j-2].player!='w')
                {
                    board[i+1][j-2].wTarget++;
                    //check if attack king
                    if (board[i+1][j-2].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-1>=0&&i+2<8)
            {
                //if the destination is not teammate
                if (board[i+2][j-1].player!='w')
                {
                    board[i+2][j-1].wTarget++;
                    //check if attack king
                    if (board[i+2][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j+2<8&&i-1>=0)
            {
                //if the destination is not teammate
                if (board[i-1][j+2].player!='w')
                {
                    board[i-1][j+2].wTarget++;
                    //check if attack king
                    if (board[i-1][j+2].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j+1<8&&i-2>=0)
            {
                //if the destination is not teammate
                if (board[i-2][j+1].player!='w')
                {
                    board[i-2][j+1].wTarget++;
                    //check if attack king
                    if (board[i-2][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-2>=0&&i-1>=0)
            {
                //if the destination is not teammate
                if (board[i-1][j-2].player!='w')
                {
                    board[i-1][j-2].wTarget++;
                    //check if attack king
                    if (board[i-1][j-2].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-1>=0&&i-2>=0)
            {
                //if the destination is not teammate
                if (board[i-2][j-1].player!='w')
                {
                    board[i-2][j-1].wTarget++;
                    //check if attack king
                    if (board[i-2][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
        }
        else if(board[i][j].player == 'b')
        {
            //check the eight directions that knight can move to.
            if (j+2<8&&i+1<8)
            {
                //if the destination is not teammate
                if (board[i+1][j+2].player!='b')
                {
                    board[i+1][j+2].bTarget++;
                    //check if attack king
                    if (board[i+1][j+2].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j+1<8&&i+2<8)
            {
                //if the destination is not teammate
                if (board[i+2][j+1].player!='b')
                {
                    board[i+2][j+1].bTarget++;
                    //check if attack king
                    if (board[i+2][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-2>=0&&i+1<8)
            {
                //if the destination is not teammate
                if (board[i+1][j-2].player!='b')
                {
                    board[i+1][j-2].bTarget++;
                    //check if attack king
                    if (board[i+1][j-2].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-1>=0&&i+2<8)
            {
                //if the destination is not teammate
                if (board[i+2][j-1].player!='b')
                {
                    board[i+2][j-1].bTarget++;
                    //check if attack king
                    if (board[i+2][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j+2<8&&i-1>=0)
            {
                //if the destination is not teammate
                if (board[i-1][j+2].player!='b')
                {
                    board[i-1][j+2].bTarget++;
                    //check if attack king
                    if (board[i-1][j+2].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j+1<8&&i-2>=0)
            {
                //if the destination is not teammate
                if (board[i-2][j+1].player!='b')
                {
                    board[i-2][j+1].bTarget++;
                    //check if attack king
                    if (board[i-2][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-2>=0&&i-1>=0)
            {
                //if the destination is not teammate
                if (board[i-1][j-2].player!='b')
                {
                    board[i-1][j-2].bTarget++;
                    //check if attack king
                    if (board[i-1][j-2].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if (j-1>=0&&i-2>=0)
            {
                //if the destination is not teammate
                if (board[i-2][j-1].player!='b')
                {
                    board[i-2][j-1].bTarget++;
                    //check if attack king
                    if (board[i-2][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
        }
    }
    //if the input board's piece type is Rook.
    else if(board[i][j].chessType == "Rook")
    {
        //check which side it is.
        if(board[i][j].player == 'w')
        {
            //check down side.
            if(i+1<8)
            {
                //run to the edge of board
                for (int k = i+1;k<8;k++)
                {
                    //if touch target or teammate, stop checking
                    if (board[k][j].player=='b')
                    {
                        board[k][j].wTarget++;
                        //check if attack king
                        if (board[k][j].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //check up side.
            if(i-1>=0)
            {
                //run to the edge of board
                for (int k = i-1;k>=0;k--)
                {
                    //if touch target or teammate, stop checking
                    if (board[k][j].player=='b')
                    {
                        board[k][j].wTarget++;
                        //check if attack king
                        if (board[k][j].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //check right side.
            if(j+1<8)
            {
                //run to the edge of board
                for (int k = j+1;k<8;k++)
                {
                    //if touch target or teammate, stop checking
                    if (board[i][k].player=='b')
                    {
                        board[i][k].wTarget++;
                        //check if attack king
                        if (board[i][k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //check left side.
            if(j-1>=0)
            {
                //run to the edge of board
                for (int k = j-1;k>=0;k--)
                {
                    //if touch target or teammate, stop checking
                    if (board[i][k].player=='b')
                    {
                        board[i][k].wTarget++;
                        //check if attack king
                        if (board[i][k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //check down side.
            if(i+1<8)
            {
                //run to the edge of board
                for (int k = i+1;k<8;k++)
                {
                    //if touch target or teammate, stop checking
                    if (board[k][j].player=='w')
                    {
                        board[k][j].bTarget++;
                        //check if attack king
                        if (board[k][j].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //check up side.
            if(i-1>=0)
            {
                //run to the edge of board
                for (int k = i-1;k>=0;k--)
                {
                    //if touch target or teammate, stop checking
                    if (board[k][j].player=='w')
                    {
                        board[k][j].bTarget++;
                        //check if attack king
                        if (board[k][j].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //check right side.
            if(j+1<8)
            {
                //run to the edge of board
                for (int k = j+1;k<8;k++)
                {
                    //if touch target or teammate, stop checking
                    if (board[i][k].player=='w')
                    {
                        board[i][k].bTarget++;
                        //check if attack king
                        if (board[i][k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //check left side.
            if(j-1>=0)
            {
                //run to the edge of board
                for (int k = j-1;k>=0;k--)
                {
                    //if touch target or teammate, stop checking
                    if (board[i][k].player=='w')
                    {
                        board[i][k].bTarget++;
                        //check if attack king
                        if (board[i][k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
    //if the input board's piece type is Bishop.
    else if(board[i][j].chessType == "Bishop")
    {
        //check which side it is.
        if (board[i][j].player == 'w')
        {
            //run to down edge or right edge.
            for (int k = 1;k<8;k++)
            {

                if (i+k<8&&j+k<8)
                {
                    //if touch target or teammate, stop checking
                    if (board[i+k][j+k].player=='b')
                    {
                        board[i+k][j+k].wTarget++;
                        //check if attack king
                        if (board[i+k][j+k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //run to down edge or left edge.
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j-k>=0)
                {
                    //if touch target or teammate, stop checking
                    if (board[i+k][j-k].player=='b')
                    {
                        board[i+k][j-k].wTarget++;
                        //check if attack king
                        if (board[i+k][j-k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //run to up edge or right edge.
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j+k<8)
                {
                    //if touch target or teammate, stop checking
                    if (board[i-k][j+k].player=='b')
                    {
                        board[i-k][j+k].wTarget++;
                        //check if attack king
                        if (board[i-k][j+k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //run to up edge or left edge.
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j-k>=0)
                {

                    //if touch target or teammate, stop checking
                    if (board[i-k][j-k].player=='b')
                    {
                        board[i-k][j-k].wTarget++;
                        //check if attack king
                        if (board[i-k][j-k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to down edge or right edge.
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j+k<8)
                {
                    //if touch target or teammate, stop checking
                    if (board[i+k][j+k].player=='w')
                    {
                        board[i+k][j+k].bTarget++;
                        //check if attack king
                        if (board[i+k][j+k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to down edge or left edge.
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j-k>=0)
                {
                    //if touch target or teammate, stop checking
                    if (board[i+k][j-k].player=='w')
                    {
                        board[i+k][j-k].bTarget++;
                        //check if attack king
                        if (board[i+k][j-k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //run to up edge or right edge.
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j+k<8)
                {
                    //if touch target or teammate, stop checking
                    if (board[i-k][j+k].player=='w')
                    {
                        board[i-k][j+k].bTarget++;
                        //check if attack king
                        if (board[i-k][j+k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //run to up edge or left edge.
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j-k>=0)
                {
                    //if touch target or teammate, stop checking
                    if (board[i-k][j-k].player=='w')
                    {
                        board[i-k][j-k].bTarget++;
                        //check if attack king
                        if (board[i-k][j-k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
    //if the input board's piece type is Queen.
    else if(board[i][j].chessType == "Queen")
    {
        //check which side it is.
        if (board[i][j].player == 'w')
        {
            //run to down edge or right edge.
            for (int k = 1;k<8;k++)
            {
                //if touch target or teammate, stop checking
                if (i+k<8&&j+k<8)
                {
                    if (board[i+k][j+k].player=='b')
                    {
                        board[i+k][j+k].wTarget++;
                        //check if attack king
                        if (board[i+k][j+k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to down edge or left edge.
            for (int k = 1;k<8;k++)
            {
                //if touch target or teammate, stop checking
                if (i+k<8&&j-k>=0)
                {
                    if (board[i+k][j-k].player=='b')
                    {
                        board[i+k][j-k].wTarget++;
                        //check if attack king
                        if (board[i+k][j-k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to up edge or right edge.
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j+k<8)
                {
                    //if touch target or teammate, stop checking
                    if (board[i-k][j+k].player=='b')
                    {
                        board[i-k][j+k].wTarget++;
                        //check if attack king
                        if (board[i-k][j+k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to up edge or left edge.
            for (int k = 1;k<8;k++)
            {
                //if touch target or teammate, stop checking
                if (i-k>=0&&j-k>=0)
                {
                    if (board[i-k][j-k].player=='b')
                    {
                        board[i-k][j-k].wTarget++;
                        //check if attack king
                        if (board[i-k][j-k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //check down side.
            if(i+1<8)
            {
                for (int k = i+1;k<8;k++)
                {
                    //if touch target or teammate, stop checking
                    if (board[k][j].player=='b')
                    {
                        board[k][j].wTarget++;
                        //check if attack king
                        if (board[k][j].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //check up side.
            if(i-1>=0)
            {
                for (int k = i-1;k>=0;k--)
                {
                    //if touch target or teammate, stop checking
                    if (board[k][j].player=='b')
                    {
                        board[k][j].wTarget++;
                        //check if attack king
                        if (board[k][j].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //check right side.
            if(j+1<8)
            {
                for (int k = j+1;k<8;k++)
                {
                    //if touch target or teammate, stop checking
                    if (board[i][k].player=='b')
                    {
                        board[i][k].wTarget++;
                        //check if attack king
                        if (board[i][k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //check left side.
            if(j-1>=0)
            {
                for (int k = j-1;k>=0;k--)
                {
                    //if touch target or teammate, stop checking
                    if (board[i][k].player=='b')
                    {
                        board[i][k].wTarget++;
                        //check if attack king
                        if (board[i][k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to down edge or right edge.
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j+k<8)
                {
                    //if touch target or teammate, stop checking
                    if (board[i+k][j+k].player=='w')
                    {
                        board[i+k][j+k].bTarget++;
                        //check if attack king
                        if (board[i+k][j+k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to down edge or left edge.
            for (int k = 1;k<8;k++)
            {
                if (i+k<8&&j-k>=0)
                {
                    //if touch target or teammate, stop checking
                    if (board[i+k][j-k].player=='w')
                    {
                        board[i+k][j-k].bTarget++;
                        //check if attack king
                        if (board[i+k][j-k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to up edge or right edge.
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j+k<8)
                {
                    //if touch target or teammate, stop checking
                    if (board[i-k][j+k].player=='w')
                    {
                        board[i-k][j+k].bTarget++;
                        //check if attack king
                        if (board[i-k][j+k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //run to up edge or left edge.
            for (int k = 1;k<8;k++)
            {
                if (i-k>=0&&j-k>=0)
                {
                    //if touch target or teammate, stop checking
                    if (board[i-k][j-k].player=='w')
                    {
                        board[i-k][j-k].bTarget++;
                        //check if attack king
                        if (board[i-k][j-k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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

            //check down side.
            if(i+1<8)
            {
                for (int k = i+1;k<8;k++)
                {
                    //if touch target or teammate, stop checking
                    if (board[k][j].player=='w')
                    {
                        board[k][j].bTarget++;
                        //check if attack king
                        if (board[k][j].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //check up side.
            if(i-1>=0)
            {
                for (int k = i-1;k>=0;k--)
                {
                    //if touch target or teammate, stop checking
                    if (board[k][j].player=='w')
                    {
                        board[k][j].bTarget++;
                        //check if attack king
                        if (board[k][j].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //check right side.
            if(j+1<8)
            {
                for (int k = j+1;k<8;k++)
                {
                    //if touch target or teammate, stop checking
                    if (board[i][k].player=='w')
                    {
                        board[i][k].bTarget++;
                        //check if attack king
                        if (board[i][k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
            //check left side.
            if(j-1>=0)
            {
                for (int k = j-1;k>=0;k--)
                {
                    //if touch target or teammate, stop checking
                    if (board[i][k].player=='w')
                    {
                        board[i][k].bTarget++;
                        //check if attack king
                        if (board[i][k].chessType=="King")
                        {
                            kingAttack = 1;
                        }
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
    //if the input board's piece type is King.
    else if(board[i][j].chessType == "King")
    {
        //check which side it is.
        if (board[i][j].player == 'w')
        {
            //check the 8 possible postions
            if(i+1<8)
            {
                if(board[i+1][j].player != 'w')
                {
                    board[i+1][j].wTarget++;
                    //check if attack king
                    if (board[i+1][j].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i-1>=0)
            {
                if(board[i-1][j].player != 'w')
                {
                    board[i-1][j].wTarget++;
                    //check if attack king
                    if ( board[i-1][j].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(j+1<8)
            {
                if(board[i][j+1].player != 'w')
                {
                    board[i][j+1].wTarget++;
                    //check if attack king
                    if (board[i][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(j-1>=0)
            {
                if(board[i][j-1].player != 'w')
                {
                    board[i][j-1].wTarget++;
                    //check if attack king
                    if (board[i][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i+1<8&&j+1<8)
            {
                if(board[i+1][j+1].player != 'w')
                {
                    board[i+1][j+1].wTarget++;
                    //check if attack king
                    if (board[i+1][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i-1>=0&&j+1<8)
            {
                if(board[i-1][j+1].player != 'w')
                {
                    board[i-1][j+1].wTarget++;
                    //check if attack king
                    if (board[i-1][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i+1<8&&j-1>=0)
            {
                if(board[i+1][j-1].player != 'w')
                {
                    board[i+1][j-1].wTarget++;
                    //check if attack king
                    if (board[i+1][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i-1>=0&&j-1>=0)
            {
                if(board[i-1][j-1].player != 'w')
                {
                    board[i-1][j-1].wTarget++;
                    //check if attack king
                    if (board[i-1][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
        }
        else if (board[i][j].player == 'b')
        {
            //check the 8 possible postions
            if(i+1<8)
            {
                if(board[i+1][j].player != 'b')
                {
                    board[i+1][j].bTarget++;
                    //check if attack king
                    if (board[i+1][j].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i-1>=0)
            {
                if(board[i-1][j].player != 'b')
                {
                    board[i-1][j].bTarget++;
                    //check if attack king
                    if (board[i-1][j].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(j+1<8)
            {
                if(board[i][j+1].player != 'b')
                {
                    board[i][j+1].bTarget++;
                    //check if attack king
                    if (board[i][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(j-1>=0)
            {
                if(board[i][j-1].player != 'b')
                {
                    board[i][j-1].bTarget++;
                    //check if attack king
                    if (board[i][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i+1<8&&j+1<8)
            {
                if(board[i+1][j+1].player != 'b')
                {
                    board[i+1][j+1].bTarget++;
                    //check if attack king
                    if (board[i+1][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i-1>=0&&j+1<8)
            {
                if(board[i-1][j+1].player != 'b')
                {
                    board[i-1][j+1].bTarget++;
                    //check if attack king
                    if (board[i-1][j+1].chessType=="King")
                    {
                        kingAttack = 1;
                    }

                }
            }
            if(i+1<8&&j-1>=0)
            {
                if(board[i+1][j-1].player != 'b')
                {
                    board[i+1][j-1].bTarget++;
                    //check if attack king
                    if (board[i+1][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
            if(i-1>=0&&j-1>=0)
            {
                if(board[i-1][j-1].player != 'b')
                {
                    board[i-1][j-1].bTarget++;
                    //check if attack king
                    if (board[i-1][j-1].chessType=="King")
                    {
                        kingAttack = 1;
                    }
                }
            }
        }
    }
    return kingAttack;
}

//intent: compute the number of possible chess pieces targeting each of the squares
//pre: none
//post: the number of targeting chess pieces are store
void GameManager::computeTarget()
{
    //reset wTargets and bTarget
    for (int i = 0;i<8;i++)
    {
        for (int k = 0;k<8;k++)
        {
            board[i][k].wTarget = 0;
            board[i][k].bTarget = 0;
        }
    }
    blackKingBeenAttackBy[0]=0;
    blackKingBeenAttackBy[1]=0;
    whiteKingBeenAttackBy[0]=0;
    whiteKingBeenAttackBy[1]=0;
    //if there has piece, than count where can it attack, and record it to wTargets and bTarget
    for (int i = 0;i<8;i++)
    {
        for (int j = 0;j < 8;j++)
        {

            if (board[i][j].ifHavePiece)
            {
                if(check(i,j,board))
                {
                    if(board[i][j].player== 'w')
                    {
                        blackKingBeenAttackBy[0]=i;
                        blackKingBeenAttackBy[1]=j;
                    }
                    else if(board[i][j].player== 'b')
                    {
                        whiteKingBeenAttackBy[0]=i;
                        whiteKingBeenAttackBy[1]=j;
                    }
                }

            }
        }
    }
}

//intent: record the current board into curBoard
//pre: none
//post: board is stored into curBoard
void GameManager::recordCurBoard()
{

    //store the neccessary info for each square on the chess board
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            curBoard.curBoard[i][j].ifHavePiece = board[i][j].ifHavePiece;
            curBoard.curBoard[i][j].wTarget = board[i][j].wTarget;
            curBoard.curBoard[i][j].bTarget = board[i][j].bTarget;
            curBoard.curBoard[i][j].player = board[i][j].player;
            curBoard.curBoard[i][j].chessType = board[i][j].chessType;
            curBoard.curBoard[i][j].index = board[i][j].index;
            curBoard.curBoard[i][j].canMove = board[i][j].canMove;

            //if king or pawn store the special values needed for enpassant, castle,
            if(board[i][j].ifHavePiece && board[i][j].player == 'w' && board[i][j].chessType == "Rook")
            {
                curBoard.curBoard[i][j].ifRookMove = White.rooks[board[i][j].index].ifMove;
            }
            else if(board[i][j].ifHavePiece && board[i][j].player == 'b' && board[i][j].chessType == "Rook")
            {
                curBoard.curBoard[i][j].ifRookMove = Black.rooks[board[i][j].index].ifMove;
            }
            else if(board[i][j].ifHavePiece && board[i][j].player == 'w' && board[i][j].chessType == "Pawn")
            {
                curBoard.curBoard[i][j].ifPawnMove2Step = White.pawns[board[i][j].index].ifmove2Step;
                curBoard.curBoard[i][j].inPawnNextTurn = White.pawns[board[i][j].index].inNextTurn;
            }
            else if(board[i][j].ifHavePiece && board[i][j].player == 'b' && board[i][j].chessType == "Pawn")
            {
                curBoard.curBoard[i][j].ifPawnMove2Step = Black.pawns[board[i][j].index].ifmove2Step;
                curBoard.curBoard[i][j].inPawnNextTurn = Black.pawns[board[i][j].index].inNextTurn;
            }
        }
    }

    //store player turn
    curBoard.ifWhiteKingMove = White.king.ifMove;
    curBoard.ifBlackKingMove = Black.king.ifMove;
    curBoard.playerTurn = playerTurn;
}

//intent: judge win or lose
int GameManager::judgeWinOrLose()
{
    bool moveStillCheck = false;
    vector<vector<int>> surroundPos = {{0,1},{0,-1},{1,0},{1,-1},{1,1},{-1,1},{-1,0},{-1,1}};
    std::string tempAttackerChessType;
    int tempAttackerIndex = 0;
    bool tempAttackerifHavePiece = false;
    char tempAttackerPlayer = '0';


    for (vector<int> &iter : surroundPos) {

        if(board[White.king.y + iter[0]][White.king.x + iter[1]].bTarget == 0
            && board[White.king.y + iter[0]][White.king.x + iter[1]].ifHavePiece == false)
        {
            return gameContinue;
        }

        if(board[Black.king.y + iter[0]][Black.king.x + iter[1]].bTarget == 0
            && board[Black.king.y + iter[0]][Black.king.x + iter[1]].ifHavePiece == false)
        {
            return gameContinue;
        }

        if(board[White.king.y + iter[0]][White.king.x + iter[1]].player == 'b')
        {
            tempAttackerIndex = board[White.king.y + iter[0]][White.king.x + iter[1]].index;
            tempAttackerChessType = board[White.king.y + iter[0]][White.king.x + iter[1]].chessType;
            tempAttackerifHavePiece = board[White.king.y + iter[0]][White.king.x + iter[1]].ifHavePiece;
            tempAttackerPlayer = board[White.king.y + iter[0]][White.king.x + iter[1]].player;

            board[White.king.y + iter[0]][White.king.x + iter[1]].index = board[White.king.y][White.king.x].index;
            board[White.king.y + iter[0]][White.king.x + iter[1]].chessType = board[White.king.y][White.king.x].chessType;
            board[White.king.y + iter[0]][White.king.x + iter[1]].ifHavePiece = board[White.king.y][White.king.x].ifHavePiece;
            board[White.king.y + iter[0]][White.king.x + iter[1]].player = board[White.king.y][White.king.x].player;

            board[White.king.y][White.king.x].index = 0;
            board[White.king.y][White.king.x].chessType = "0";
            board[White.king.y][White.king.x].ifHavePiece = false;
            board[White.king.y][White.king.x].player = '0';

            computeTarget();

            board[White.king.y][White.king.x].index = board[White.king.y + iter[0]][White.king.x + iter[1]].index;
            board[White.king.y][White.king.x].chessType = board[White.king.y + iter[0]][White.king.x + iter[1]].chessType;
            board[White.king.y][White.king.x].ifHavePiece = board[White.king.y + iter[0]][White.king.x + iter[1]].ifHavePiece;
            board[White.king.y][White.king.x].player = board[White.king.y + iter[0]][White.king.x + iter[1]].player;

            board[White.king.y + iter[0]][White.king.x + iter[1]].index = tempAttackerIndex;
            board[White.king.y + iter[0]][White.king.x + iter[1]].chessType = tempAttackerChessType;
            board[White.king.y + iter[0]][White.king.x + iter[1]].ifHavePiece = tempAttackerifHavePiece;
            board[White.king.y + iter[0]][White.king.x + iter[1]].player = tempAttackerPlayer;

            if(board[White.king.y + iter[0]][White.king.x + iter[1]].bTarget >= 1)
            {
                moveStillCheck = true;
                break;
            }

        }
        else if(board[Black.king.y + iter[0]][Black.king.x + iter[1]].player == 'w')
        {
            tempAttackerIndex = board[Black.king.y + iter[0]][Black.king.x + iter[1]].index;
            tempAttackerChessType = board[Black.king.y + iter[0]][Black.king.x + iter[1]].chessType;
            tempAttackerifHavePiece = board[Black.king.y + iter[0]][Black.king.x + iter[1]].ifHavePiece;
            tempAttackerPlayer = board[Black.king.y + iter[0]][Black.king.x + iter[1]].player;

            board[Black.king.y + iter[0]][Black.king.x + iter[1]].index = board[Black.king.y][Black.king.x].index;
            board[Black.king.y + iter[0]][Black.king.x + iter[1]].chessType = board[Black.king.y][Black.king.x].chessType;
            board[Black.king.y + iter[0]][Black.king.x + iter[1]].ifHavePiece = board[Black.king.y][Black.king.x].ifHavePiece;
            board[Black.king.y + iter[0]][Black.king.x + iter[1]].player = board[Black.king.y][Black.king.x].player;

            board[Black.king.y][Black.king.x].index = 0;
            board[Black.king.y][Black.king.x].chessType = "0";
            board[Black.king.y][Black.king.x].ifHavePiece = false;
            board[Black.king.y][Black.king.x].player = '0';

            computeTarget();

            board[Black.king.y][Black.king.x].index = board[Black.king.y + iter[0]][Black.king.x + iter[1]].index;
            board[Black.king.y][Black.king.x].chessType = board[Black.king.y + iter[0]][Black.king.x + iter[1]].chessType;
            board[Black.king.y][Black.king.x].ifHavePiece = board[Black.king.y + iter[0]][Black.king.x + iter[1]].ifHavePiece;
            board[Black.king.y][Black.king.x].player = board[Black.king.y + iter[0]][Black.king.x + iter[1]].player;

            board[Black.king.y + iter[0]][Black.king.x + iter[1]].index = tempAttackerIndex;
            board[Black.king.y + iter[0]][Black.king.x + iter[1]].chessType = tempAttackerChessType;
            board[Black.king.y + iter[0]][Black.king.x + iter[1]].ifHavePiece = tempAttackerifHavePiece;
            board[Black.king.y + iter[0]][Black.king.x + iter[1]].player = tempAttackerPlayer;

            if(board[Black.king.y + iter[0]][Black.king.x + iter[1]].wTarget >= 1)
            {
                moveStillCheck = true;
                break;
            }
        }
    }

    //black win
    //king position is attacked by more than two chess
    if(board[White.king.y][White.king.x].bTarget >= 2)
    {
        //check eight surrounding squares to see if king can move there
        //up
        if(((ifPosInBoard(White.king.y - 1, White.king.x - 1) && (board[White.king.y - 1][White.king.x - 1].bTarget > 0)) || board[White.king.y - 1][White.king.x - 1].player == 'w' || !ifPosInBoard(White.king.y - 1, White.king.x - 1))
            //down
            && ((ifPosInBoard(White.king.y - 1, White.king.x + 1) && (board[White.king.y - 1][White.king.x + 1].bTarget > 0)) || board[White.king.y - 1][White.king.x + 1].player == 'w' || !ifPosInBoard(White.king.y - 1, White.king.x + 1))
            //left
            && ((ifPosInBoard(White.king.y - 1, White.king.x) && (board[White.king.y - 1][White.king.x].bTarget > 0)) || board[White.king.y - 1][White.king.x].player == 'w' || !ifPosInBoard(White.king.y - 1, White.king.x))
            //right
            && ((ifPosInBoard(White.king.y + 1, White.king.x - 1) && (board[White.king.y + 1][White.king.x - 1].bTarget > 0)) || board[White.king.y + 1][White.king.x - 1].player == 'w' || !ifPosInBoard(White.king.y + 1, White.king.x - 1))
            //left up
            && ((ifPosInBoard(White.king.y + 1, White.king.x + 1) && (board[White.king.y + 1][White.king.x + 1].bTarget > 0)) || board[White.king.y + 1][White.king.x + 1].player == 'w' || !ifPosInBoard(White.king.y + 1, White.king.x + 1))
            //right up
            && ((ifPosInBoard(White.king.y + 1, White.king.x) && (board[White.king.y + 1][White.king.x].bTarget > 0)) || board[White.king.y + 1][White.king.x].player == 'w' || !ifPosInBoard(White.king.y + 1, White.king.x))
            //left down
            && ((ifPosInBoard(White.king.y, White.king.x + 1) && (board[White.king.y][White.king.x + 1].bTarget > 0)) || board[White.king.y][White.king.x + 1].player == 'w' || !ifPosInBoard(White.king.y, White.king.x + 1))
            //right down
            && ((ifPosInBoard(White.king.y, White.king.x - 1) && (board[White.king.y][White.king.x - 1].bTarget > 0)) || board[White.king.y][White.king.x - 1].player == 'w' || ifPosInBoard(White.king.y, White.king.x - 1)))
        {
            return blackWin;
        }
    }
    //white win
    //king position is attacked by more than two chess
    else if(board[Black.king.y][Black.king.x].wTarget >= 2)
    {

        //check eight surrounding squares to see if king can move there
        //up
        if(((ifPosInBoard(Black.king.y - 1, Black.king.x - 1) && (board[Black.king.y - 1][Black.king.x - 1].wTarget > 0)) || board[Black.king.y - 1][Black.king.x - 1].player == 'b' || !ifPosInBoard(Black.king.y - 1, Black.king.x - 1))
            //down
            && ((ifPosInBoard(Black.king.y - 1, Black.king.x + 1) && (board[Black.king.y - 1][Black.king.x + 1].wTarget > 0)) || board[Black.king.y - 1][Black.king.x + 1].player == 'b' || !ifPosInBoard(Black.king.y - 1, Black.king.x + 1))
            //left
            && ((ifPosInBoard(Black.king.y - 1, Black.king.x) && (board[Black.king.y - 1][Black.king.x].wTarget > 0)) || board[Black.king.y - 1][Black.king.x].player == 'b' || !ifPosInBoard(Black.king.y - 1, Black.king.x))
            //right
            && ((ifPosInBoard(Black.king.y + 1, Black.king.x - 1) && (board[Black.king.y + 1][Black.king.x - 1].wTarget > 0)) || board[Black.king.y + 1][Black.king.x - 1].player == 'b' || !ifPosInBoard(Black.king.y + 1, Black.king.x - 1))
            //left up
            && ((ifPosInBoard(Black.king.y + 1, Black.king.x + 1) && (board[Black.king.y + 1][Black.king.x + 1].wTarget > 0)) || board[Black.king.y + 1][Black.king.x + 1].player == 'b' || !ifPosInBoard(Black.king.y + 1, Black.king.x + 1))
            //right up
            && ((ifPosInBoard(Black.king.y + 1, Black.king.x) && (board[Black.king.y + 1][Black.king.x].wTarget > 0)) || board[Black.king.y + 1][Black.king.x].player == 'b' || !ifPosInBoard(Black.king.y + 1, Black.king.x))
            //left down
            && ((ifPosInBoard(Black.king.y, Black.king.x + 1) && (board[Black.king.y][Black.king.x + 1].wTarget > 0)) || board[Black.king.y][Black.king.x + 1].player == 'b' || !ifPosInBoard(Black.king.y, Black.king.x + 1))
            //right down
            && ((ifPosInBoard(Black.king.y, Black.king.x - 1) && (board[Black.king.y][Black.king.x - 1].wTarget > 0)) || board[Black.king.y][Black.king.x - 1].player == 'b' || ifPosInBoard(Black.king.y, Black.king.x - 1)))
        {
            return whiteWin;
        }
    }
    else if(board[White.king.y][White.king.x].bTarget >= 1 || moveStillCheck)//there's 1 targeting the king
    {
        //check eight surrounding squares to see if king can move there
        //up
        if(((ifPosInBoard(White.king.y - 1, White.king.x - 1) && (board[White.king.y - 1][White.king.x - 1].bTarget > 0)) || board[White.king.y - 1][White.king.x - 1].player == 'w' || !ifPosInBoard(White.king.y - 1, White.king.x - 1))
            //down
            && ((ifPosInBoard(White.king.y - 1, White.king.x + 1) && (board[White.king.y - 1][White.king.x + 1].bTarget > 0)) || board[White.king.y - 1][White.king.x + 1].player == 'w' || !ifPosInBoard(White.king.y - 1, White.king.x + 1))
            //left
            && ((ifPosInBoard(White.king.y - 1, White.king.x) && (board[White.king.y - 1][White.king.x].bTarget > 0)) || board[White.king.y - 1][White.king.x].player == 'w' || !ifPosInBoard(White.king.y - 1, White.king.x))
            //right
            && ((ifPosInBoard(White.king.y + 1, White.king.x - 1) && (board[White.king.y + 1][White.king.x - 1].bTarget > 0)) || board[White.king.y + 1][White.king.x - 1].player == 'w' || !ifPosInBoard(White.king.y + 1, White.king.x - 1))
            //left up
            && ((ifPosInBoard(White.king.y + 1, White.king.x + 1) && (board[White.king.y + 1][White.king.x + 1].bTarget > 0)) || board[White.king.y + 1][White.king.x + 1].player == 'w' || !ifPosInBoard(White.king.y + 1, White.king.x + 1))
            //right up
            && ((ifPosInBoard(White.king.y + 1, White.king.x) && (board[White.king.y + 1][White.king.x].bTarget > 0)) || board[White.king.y + 1][White.king.x].player == 'w' || !ifPosInBoard(White.king.y + 1, White.king.x))
            //left down
            && ((ifPosInBoard(White.king.y, White.king.x + 1) && (board[White.king.y][White.king.x + 1].bTarget > 0)) || board[White.king.y][White.king.x + 1].player == 'w' || !ifPosInBoard(White.king.y, White.king.x + 1))
            //right down
            && ((ifPosInBoard(White.king.y, White.king.x - 1) && (board[White.king.y][White.king.x - 1].bTarget > 0)) || board[White.king.y][White.king.x - 1].player == 'w' || ifPosInBoard(White.king.y, White.king.x - 1)))
        {
            //info of the attacking piece
            int attackPiecerow = whiteKingBeenAttackBy[0];
            int attackPiececol = whiteKingBeenAttackBy[1];
            string attackPieceName = board[attackPiecerow][attackPiececol].chessType;
            int attackPieceIndex = board[attackPiecerow][attackPiececol].index;
            char attackPiecePlayer = 'b';

            //store the path of the attacking piece
            vector<vector<int>> attackPiecePaths;

            //if king is in this path
            bool ifKingInPath = 0;
            //if attack path can be blocked
            bool ifcanBlock = false;

            //calculating attacking paths
            //iterate each square of each path for attacking chess piece, store the path that can attack the king
            if(attackPieceName == "Rook")
            {
                //if the paths before can't attack the king
                if(!ifKingInPath)
                {
                    for(int i = 1; i < 8;i++)
                    {

                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {

                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                                break;
                            }
                        }
                    }

                }
                //if the path can't attack the king, reset the vector that stores the path
                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                //if the paths before can't attack the king
                if(!ifKingInPath)
                {
                    //down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                                break;
                            }
                        }
                    }
                }
                //if the path can't attack the king, reset the vector that stores the path
                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                //if the paths before can't attack the king
                if(!ifKingInPath)
                {
                    //right
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                        else if(boardChessCondition(attackPiecerow, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                                break;
                            }
                        }
                    }
                }
                //if the path can't attack the king, reset the vector that stores the path
                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                //if the paths before can't attack the king, then must be this path
                if(!ifKingInPath)
                {
                    //left
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                        else if(boardChessCondition(attackPiecerow, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                                break;
                            }
                        }
                    }
                }

            }
            else if(attackPieceName == "Bishop") //same as rook, but different pattern of movement
            {

                if(!ifKingInPath)
                {
                    //right up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                                break;
                            }
                        }
                    }

                }
                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //right down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath){
                    //left up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                                break;
                            }
                        }
                    }
                }
                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                                break;
                            }
                        }
                    }

                }


            }
            else if(attackPieceName == "Queen") //same as rook, but different pattern of movement
            {
                if(!ifKingInPath)
                {

                    //up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }


                if(!ifKingInPath)
                {
                    //right
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                        else if(boardChessCondition(attackPiecerow, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                        else if(boardChessCondition(attackPiecerow, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //right up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //right down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                                break;
                            }
                        }
                    }
                }


                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                                break;
                            }
                        }
                    }
                }

            }

            //print path on to terminal
            for (vector<int> &x: attackPiecePaths)
            {
                cout << x[0] << " " << x[1] << endl;;
            }

            //check if knight or pawn, since their attack on the king can't be stopped by blocking their paths
            //can only be stopped if they are taken
            if(attackPieceName == "Pawn" || attackPieceName == "Knight")
            {
                //if no piece can take the attacker, then black win
                if(board[attackPiecerow][attackPiececol].wTarget == 0)
                {
                    return blackWin;
                }

                //check for all pieces that can take the attacker, see after taking the attacker, is the king still checked,
                //if so for all possible chess pieces then must be check mate
                for (int row = 0; row < 8; ++row) {
                    for (int col = 0; col < 8; ++col) {
                        //if the chess piece on the current sauare is white, and is not the king itself
                        if(board[row][col].ifHavePiece && board[row][col].player == 'w' && board[row][col].chessType != "King")
                        {
                            //calculate the moves of this chess piece and check if it can take the attacker
                            //if so then try to move to see if king still checked, if so, check mate
                            showCanMove(row,col);

                            if(board[attackPiecerow][attackPiececol].canMove == true)
                            {
                                board[attackPiecerow][attackPiececol].index = board[row][col].index;
                                board[attackPiecerow][attackPiececol].chessType = board[row][col].chessType;
                                board[attackPiecerow][attackPiececol].ifHavePiece = true;
                                board[attackPiecerow][attackPiececol].player = 'w';

                                board[row][col].index = 0;
                                board[row][col].chessType = "0";
                                board[row][col].ifHavePiece = false;
                                board[row][col].player = '0';

                                computeTarget();

                                board[row][col].index = board[attackPiecerow][attackPiececol].index;
                                board[row][col].chessType = board[attackPiecerow][attackPiececol].chessType;
                                board[row][col].ifHavePiece = true;
                                board[row][col].player =  board[attackPiecerow][attackPiececol].player;

                                board[attackPiecerow][attackPiececol].index = attackPieceIndex;
                                board[attackPiecerow][attackPiececol].chessType = attackPieceName;
                                board[attackPiecerow][attackPiececol].ifHavePiece = true;
                                board[attackPiecerow][attackPiececol].player = attackPiecePlayer;

                                for(int i = 0; i < 8; i++)
                                {
                                    for(int j = 0; j < 8; j++)
                                    {
                                        board[i][j].canMove = false;
                                    }
                                }

                                if(board[White.king.y][White.king.x].bTarget == 0)
                                {
                                    return gameContinue;
                                }

                            }


                        }
                    }
                }

                return blackWin;

            }
            else //not pawn or knight
            {
                //if attacking path can't be blocked then black win
                for (vector<int>& iter : attackPiecePaths) {
                    if(!(board[iter[0]][iter[1]].wTarget == 0))
                    {
                        ifcanBlock = true;
                    }
                }

                if(ifcanBlock == false)
                {
                    return blackWin;
                }


                //check for all pieces that can take the attacker or block its path, see after blocking or taking the attacker, is the king still checked,
                //if so for all possible chess pieces then must be check mate
                for (int row = 0; row < 8; ++row) {
                    for (int col = 0; col < 8; ++col) {

                        //if the chess piece on the current sauare is white, and is not the king itself
                        if(board[row][col].ifHavePiece && board[row][col].player == 'w' && board[row][col].chessType != "King")
                        {

                            //calculate the moves of this chess piece and check if it can take the attacker
                            //if so then try to move to see if king still checked , if so, check mate
                            showCanMove(row,col);

                            for (vector<int>& iter : attackPiecePaths) {
                                if(board[iter[0]][iter[1]].canMove == true)
                                {
                                    board[iter[0]][iter[1]].index = board[row][col].index;
                                    board[iter[0]][iter[1]].chessType = board[row][col].chessType;
                                    board[iter[0]][iter[1]].ifHavePiece = true;
                                    board[iter[0]][iter[1]].player = 'w';

                                    board[row][col].index = 0;
                                    board[row][col].chessType = "0";
                                    board[row][col].ifHavePiece = false;
                                    board[row][col].player = '0';

                                    computeTarget();

                                    board[row][col].index = board[iter[0]][iter[1]].index;
                                    board[row][col].chessType = board[iter[0]][iter[1]].chessType;
                                    board[row][col].ifHavePiece = true;
                                    board[row][col].player =  board[iter[0]][iter[1]].player;

                                    board[iter[0]][iter[1]].index = 0;
                                    board[iter[0]][iter[1]].chessType = "0";
                                    board[iter[0]][iter[1]].ifHavePiece = false;
                                    board[iter[0]][iter[1]].player = '0';

                                    for(int i = 0; i < 8; i++)
                                    {
                                        for(int j = 0; j < 8; j++)
                                        {
                                            board[i][j].canMove = false;
                                        }
                                    }

                                    if(board[White.king.y][White.king.x].bTarget == 0)
                                    {
                                        return gameContinue;
                                    }

                                }

                            }
                            if(board[attackPiecerow][attackPiececol].canMove == true)
                            {
                                board[attackPiecerow][attackPiececol].index = board[row][col].index;
                                board[attackPiecerow][attackPiececol].chessType = board[row][col].chessType;
                                board[attackPiecerow][attackPiececol].ifHavePiece = true;
                                board[attackPiecerow][attackPiececol].player = 'w';

                                board[row][col].index = 0;
                                board[row][col].chessType = "0";
                                board[row][col].ifHavePiece = false;
                                board[row][col].player = '0';

                                computeTarget();

                                board[row][col].index = board[attackPiecerow][attackPiececol].index;
                                board[row][col].chessType = board[attackPiecerow][attackPiececol].chessType;
                                board[row][col].ifHavePiece = true;
                                board[row][col].player =  board[attackPiecerow][attackPiececol].player;

                                board[attackPiecerow][attackPiececol].index = attackPieceIndex;
                                board[attackPiecerow][attackPiececol].chessType = attackPieceName;
                                board[attackPiecerow][attackPiececol].ifHavePiece = true;
                                board[attackPiecerow][attackPiececol].player = attackPiecePlayer;

                                if(board[White.king.y][White.king.x].bTarget == 0)
                                {
                                    return gameContinue;
                                }


                            }

                        }

                    }

                }

                return blackWin;

            }
        }
    }
    else if(board[Black.king.y][Black.king.x].wTarget >= 1 || moveStillCheck) // if black king is attacked
    {

        //check eight surrounding squares to see if king can move there
        //up
        if(((ifPosInBoard(Black.king.y - 1, Black.king.x - 1) && (board[Black.king.y - 1][Black.king.x - 1].wTarget > 0)) || board[Black.king.y - 1][Black.king.x - 1].player == 'b' || !ifPosInBoard(Black.king.y - 1, Black.king.x - 1))
            //down
            && ((ifPosInBoard(Black.king.y - 1, Black.king.x + 1) && (board[Black.king.y - 1][Black.king.x + 1].wTarget > 0)) || board[Black.king.y - 1][Black.king.x + 1].player == 'b' || !ifPosInBoard(Black.king.y - 1, Black.king.x + 1))
            //left
            && ((ifPosInBoard(Black.king.y - 1, Black.king.x) && (board[Black.king.y - 1][Black.king.x].wTarget > 0)) || board[Black.king.y - 1][Black.king.x].player == 'b' || !ifPosInBoard(Black.king.y - 1, Black.king.x))
            //right
            && ((ifPosInBoard(Black.king.y + 1, Black.king.x - 1) && (board[Black.king.y + 1][Black.king.x - 1].wTarget > 0)) || board[Black.king.y + 1][Black.king.x - 1].player == 'b' || !ifPosInBoard(Black.king.y + 1, Black.king.x - 1))
            //left up
            && ((ifPosInBoard(Black.king.y + 1, Black.king.x + 1) && (board[Black.king.y + 1][Black.king.x + 1].wTarget > 0)) || board[Black.king.y + 1][Black.king.x + 1].player == 'b' || !ifPosInBoard(Black.king.y + 1, Black.king.x + 1))
            //right up
            && ((ifPosInBoard(Black.king.y + 1, Black.king.x) && (board[Black.king.y + 1][Black.king.x].wTarget > 0)) || board[Black.king.y + 1][Black.king.x].player == 'b' || !ifPosInBoard(Black.king.y + 1, Black.king.x))
            //left down
            && ((ifPosInBoard(Black.king.y, Black.king.x + 1) && (board[Black.king.y][Black.king.x + 1].wTarget > 0)) || board[Black.king.y][Black.king.x + 1].player == 'b' || !ifPosInBoard(Black.king.y, Black.king.x + 1))
            //right down
            && ((ifPosInBoard(Black.king.y, Black.king.x - 1) && (board[Black.king.y][Black.king.x - 1].wTarget > 0)) || board[Black.king.y][Black.king.x - 1].player == 'b' || ifPosInBoard(Black.king.y, Black.king.x - 1)))
        {
            //info of attacking chess piece
            int attackPiecerow = blackKingBeenAttackBy[0];
            int attackPiececol = blackKingBeenAttackBy[1];
            string attackPieceName = board[attackPiecerow][attackPiececol].chessType;
            int attackPieceIndex = board[attackPiecerow][attackPiececol].index;
            char attackPiecePlayer = 'w';
            vector<vector<int>> attackPiecePaths;
            bool ifKingInPath = 0;
            bool ifcanBlock = false;

            //calculate attack path, same as if white king is attacked, but for black king
            if(attackPieceName == "Rook")
            {
                if(!ifKingInPath)
                {
                    for(int i = 1; i < 8;i++)
                    {

                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {

                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                                break;
                            }
                        }
                    }

                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                                break;
                            }
                        }
                    }
                }
                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //right
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                        else if(boardChessCondition(attackPiecerow, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                                break;
                            }
                        }
                    }
                }


                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                        else if(boardChessCondition(attackPiecerow, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                                break;
                            }
                        }
                    }
                }

            }
            else if(attackPieceName == "Bishop")
            {
                if(!ifKingInPath)
                {
                    //right up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                                break;
                            }
                        }
                    }

                }
                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //right down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath){
                    //left up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {

                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {   if(board[attackPiecerow + i][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                                break;
                            }
                        }
                    }
                }
                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {   if(board[attackPiecerow - i][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                                break;
                            }
                        }
                    }

                }


            }
            else if(attackPieceName == "Queen")
            {
                if(!ifKingInPath)
                {

                    //up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }


                if(!ifKingInPath)
                {
                    //right
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                        else if(boardChessCondition(attackPiecerow, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol + i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                        else if(boardChessCondition(attackPiecerow, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow  ,attackPiececol - i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //right up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  + i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //right down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol + i))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol + i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol + i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol + i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  + i});
                                break;
                            }
                        }
                    }
                }

                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left up
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow + i, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow + i, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                        else if(boardChessCondition(attackPiecerow + i, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow + i][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow + i ,attackPiececol  - i});
                                break;
                            }
                        }
                    }
                }


                if(!ifKingInPath)
                {
                    attackPiecePaths.clear();
                }

                if(!ifKingInPath)
                {
                    //left down
                    for(int i = 1;i<8;i++)
                    {
                        if(!ifPosInBoard(attackPiecerow - i, attackPiececol - i))
                            break;

                        if(boardChessCondition(attackPiecerow - i, attackPiececol - i) == noChess)
                            attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                        else if(boardChessCondition(attackPiecerow - i, attackPiececol - i) == whiteChess)
                        {
                            if(attackPiecePlayer == 'w')
                            {
                                break;
                            }
                            else
                            {
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                                break;
                            }
                        }
                        else//boardChessCondition == blackChess
                        {
                            if(attackPiecePlayer == 'b')
                            {
                                break;
                            }
                            else
                            {
                                if(board[attackPiecerow - i][attackPiececol - i].chessType == "King")
                                {
                                    ifKingInPath = true;
                                }
                                attackPiecePaths.insert(attackPiecePaths.end(),{attackPiecerow - i ,attackPiececol  - i});
                                break;
                            }
                        }
                    }
                }

            }

            //same as if white king attacked
            //check if knight or pawn, since their attack on the king can't be stopped by blocking their paths
            //can only be stopped if they are taken
            if(attackPieceName == "Pawn" || attackPieceName == "Knight")
            {
                if(board[attackPiecerow][attackPiececol].bTarget == 0)
                {
                    return whiteWin;
                }

                for (int row = 0; row < 8; ++row) {
                    for (int col = 0; col < 8; ++col) {
                        if(board[row][col].player == 'b' && board[row][col].chessType != "King" && board[row][col].ifHavePiece)
                        {
                            showCanMove(row,col);

                            if(board[attackPiecerow][attackPiececol].canMove == true)
                            {
                                board[attackPiecerow][attackPiececol].index = board[row][col].index;
                                board[attackPiecerow][attackPiececol].chessType = board[row][col].chessType;
                                board[attackPiecerow][attackPiececol].ifHavePiece = true;
                                board[attackPiecerow][attackPiececol].player = 'b';

                                board[row][col].index = 0;
                                board[row][col].chessType = "0";
                                board[row][col].ifHavePiece = false;
                                board[row][col].player = '0';

                                computeTarget();

                                board[row][col].index = board[attackPiecerow][attackPiececol].index;
                                board[row][col].chessType = board[attackPiecerow][attackPiececol].chessType;
                                board[row][col].ifHavePiece = true;
                                board[row][col].player =  board[attackPiecerow][attackPiececol].player;

                                board[attackPiecerow][attackPiececol].index = attackPieceIndex;
                                board[attackPiecerow][attackPiececol].chessType = attackPieceName;
                                board[attackPiecerow][attackPiececol].ifHavePiece = true;
                                board[attackPiecerow][attackPiececol].player = attackPiecePlayer;

                                for(int i = 0; i < 8; i++)
                                {
                                    for(int j = 0; j < 8; j++)
                                    {
                                        board[i][j].canMove = false;
                                    }
                                }

                                if(board[Black.king.y][Black.king.x].wTarget == 0)
                                {
                                    return gameContinue;
                                }

                            }


                        }
                    }
                }

                return whiteWin;

            }
            else
            {
                for (vector<int>& iter : attackPiecePaths) {
                    if(!(board[iter[0]][iter[1]].wTarget == 0))
                    {
                        ifcanBlock = true;
                    }
                }

                if(ifcanBlock == false)
                {
                    return whiteWin;
                }


                for (int row = 0; row < 8; ++row) {
                    for (int col = 0; col < 8; ++col) {
                        if(board[row][col].player == 'b'&& board[row][col].chessType != "King" && board[row][col].ifHavePiece)
                        {
                            showCanMove(row,col);

                            for (vector<int>& iter : attackPiecePaths) {
                                if(board[iter[0]][iter[1]].canMove == true)
                                {
                                    board[iter[0]][iter[1]].index = board[row][col].index;
                                    board[iter[0]][iter[1]].chessType = board[row][col].chessType;
                                    board[iter[0]][iter[1]].ifHavePiece = true;
                                    board[iter[0]][iter[1]].player = 'b';

                                    board[row][col].index = 0;
                                    board[row][col].chessType = "0";
                                    board[row][col].ifHavePiece = false;
                                    board[row][col].player = '0';

                                    computeTarget();

                                    board[row][col].index = board[iter[0]][iter[1]].index;
                                    board[row][col].chessType = board[iter[0]][iter[1]].chessType;
                                    board[row][col].ifHavePiece = true;
                                    board[row][col].player =  board[iter[0]][iter[1]].player;

                                    board[iter[0]][iter[1]].index = 0;
                                    board[iter[0]][iter[1]].chessType = "0";
                                    board[iter[0]][iter[1]].ifHavePiece = false;
                                    board[iter[0]][iter[1]].player = '0';

                                    for(int i = 0; i < 8; i++)
                                    {
                                        for(int j = 0; j < 8; j++)
                                        {
                                            board[i][j].canMove = false;
                                        }
                                    }

                                    if(board[Black.king.y][Black.king.x].wTarget == 0)
                                    {
                                        return gameContinue;
                                    }

                                }

                            }

                            if(board[attackPiecerow][attackPiececol].canMove == true)
                            {
                                board[attackPiecerow][attackPiececol].index = board[row][col].index;
                                board[attackPiecerow][attackPiececol].chessType = board[row][col].chessType;
                                board[attackPiecerow][attackPiececol].ifHavePiece = true;
                                board[attackPiecerow][attackPiececol].player = 'b';

                                board[row][col].index = 0;
                                board[row][col].chessType = "0";
                                board[row][col].ifHavePiece = false;
                                board[row][col].player = '0';

                                computeTarget();

                                board[row][col].index = board[attackPiecerow][attackPiececol].index;
                                board[row][col].chessType = board[attackPiecerow][attackPiececol].chessType;
                                board[row][col].ifHavePiece = true;
                                board[row][col].player =  board[attackPiecerow][attackPiececol].player;

                                board[attackPiecerow][attackPiececol].index = attackPieceIndex;
                                board[attackPiecerow][attackPiececol].chessType = attackPieceName;
                                board[attackPiecerow][attackPiececol].ifHavePiece = true;
                                board[attackPiecerow][attackPiececol].player = attackPiecePlayer;

                                if(board[Black.king.y][Black.king.x].wTarget == 0)
                                {
                                    return gameContinue;
                                }


                            }

                        }

                    }

                }

                return whiteWin;

            }

        }
    }

    computeTarget();
    //return to game
    return gameContinue;
}

//intent: if player can move
//pre: none
//post return if player can move
void GameManager::judgeIfPlayerCanMove(char player)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j].ifHavePiece)
            {
                if(ifWhiteCanMove == false && board[i][j].player == 'w' && playerTurn == 'w')
                {
                    ifWhiteCanMove = ifPosCanMove(i, j);
                }
                else if(ifBlackCanMove == false && board[i][j].player == 'b' && playerTurn == 'b')
                {
                    ifBlackCanMove = ifPosCanMove(i, j);
                }
            }
        }
    }
}

//intent: check if chess piece at position can move (is not stuck)
//pre: none
//post: return if can move
bool GameManager::ifPosCanMove(int row, int col)
{
    if(board[row][col].chessType == "Pawn")
    {
        if(board[row][col].player == 'w')
        {
            //first step
            if(row == 6)
            {
                if(ifPosInBoard(row - 2, col) && board[row - 2][col].ifHavePiece == false && board[row - 1][col].ifHavePiece == false)
                {
                    return true;
                }
            }

            if(ifPosInBoard(row - 1, col) && board[row - 1][col].ifHavePiece == false)
            {
                return true;
            }

            if(ifPosInBoard(row - 1, col - 1) && boardChessCondition(row - 1, col - 1) == blackChess)
            {
                return true;
            }

            if(ifPosInBoard(row - 1, col + 1) && boardChessCondition(row - 1, col + 1) == blackChess)
            {
                return true;
            }

            //En passant
            if(row == 3)
            {
                //left En passant
                if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) == blackChess && board[row][col - 1].chessType == "Pawn")
                {
                    if(Black.pawns[board[row][col - 1].index].ifmove2Step == true && Black.pawns[board[row][col - 1].index].inNextTurn == true)
                    {
                        return true;
                    }
                }

                //right En passant
                if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) == blackChess && board[row][col + 1].chessType == "Pawn")
                {
                    if(Black.pawns[board[row][col + 1].index].ifmove2Step == true && Black.pawns[board[row][col + 1].index].inNextTurn == true)
                    {
                        return true;
                    }
                }
            }

            return false;
        }
        else//board[row][col].player = 'b'
        {
            //first step
            if(row == 1)
            {
                if(ifPosInBoard(row + 2, col) && board[row + 2][col].ifHavePiece == false && board[row + 1][col].ifHavePiece == false)
                {
                    return true;
                }
            }

            if(ifPosInBoard(row + 1, col) && board[row + 1][col].ifHavePiece == false)
            {
                return true;
            }

            if(ifPosInBoard(row + 1, col - 1) && boardChessCondition(row + 1, col - 1) == whiteChess)
            {
                return true;
            }

            if(ifPosInBoard(row + 1, col + 1) && boardChessCondition(row + 1, col + 1) == whiteChess)
            {
                return true;
            }

            //En passant
            if(row == 4)
            {
                //left En passant
                if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) == whiteChess && board[row][col - 1].chessType == "Pawn")
                {
                    if(White.pawns[board[row][col - 1].index].ifmove2Step == true && White.pawns[board[row][col - 1].index].inNextTurn == true)
                    {
                        return true;
                    }
                }

                //right En passant
                if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) == whiteChess && board[row][col + 1].chessType == "Pawn")
                {
                    if(White.pawns[board[row][col + 1].index].ifmove2Step == true && White.pawns[board[row][col + 1].index].inNextTurn == true)
                    {
                        return true;
                    }
                }
            }

            return false;
        }
    }
    else if(board[row][col].chessType == "Rook")
    {
        //up
        for(int i = 1; i < 8;i++)
        {
            if(!ifPosInBoard(row + i, col))
                break;

            if(boardChessCondition(row + i, col) == noChess)
                return true;
            else if(boardChessCondition(row + i, col) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row - i, col) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row, col + i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row, col - i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
        }

        return false;
    }
    else if(board[row][col].chessType == "Knight")
    {
        if(board[row][col].player == 'w')
        {
            if(ifPosInBoard(row + 2, col + 1) && boardChessCondition(row + 2, col + 1) != whiteChess)
                return true;

            if(ifPosInBoard(row + 2, col - 1) && boardChessCondition(row + 2, col - 1) != whiteChess)
                return true;

            if(ifPosInBoard(row - 2, col + 1) && boardChessCondition(row - 2, col + 1) != whiteChess)
                return true;

            if(ifPosInBoard(row - 2, col - 1) && boardChessCondition(row - 2, col - 1) != whiteChess)
                return true;

            if(ifPosInBoard(row + 1, col + 2) && boardChessCondition(row + 1, col + 2) != whiteChess)
                return true;

            if(ifPosInBoard(row + 1, col - 2) && boardChessCondition(row + 1, col - 2) != whiteChess)
                return true;

            if(ifPosInBoard(row - 1, col + 2) && boardChessCondition(row - 1, col + 2) != whiteChess)
                return true;

            if(ifPosInBoard(row - 1, col - 2) && boardChessCondition(row - 1, col - 2) != whiteChess)
                return true;

            return false;
        }
        else//board[row][col].player == 'b'
        {
            if(ifPosInBoard(row + 2, col + 1) && boardChessCondition(row + 2, col + 1) != blackChess)
                return true;

            if(ifPosInBoard(row + 2, col - 1) && boardChessCondition(row + 2, col - 1) != blackChess)
                return true;

            if(ifPosInBoard(row - 2, col + 1) && boardChessCondition(row - 2, col + 1) != blackChess)
                return true;

            if(ifPosInBoard(row - 2, col - 1) && boardChessCondition(row - 2, col - 1) != blackChess)
                return true;

            if(ifPosInBoard(row + 1, col + 2) && boardChessCondition(row + 1, col + 2) != blackChess)
                return true;

            if(ifPosInBoard(row + 1, col - 2) && boardChessCondition(row + 1, col - 2) != blackChess)
                return true;

            if(ifPosInBoard(row - 1, col + 2) && boardChessCondition(row - 1, col + 2) != blackChess)
                return true;

            if(ifPosInBoard(row - 1, col - 2) && boardChessCondition(row - 1, col - 2) != blackChess)
                return true;

            return false;
        }
    }
    else if(board[row][col].chessType == "Bishop")
    {
        //right up
        for(int i = 1;i<8;i++)
        {
            if(!ifPosInBoard(row + i, col + i))
                break;

            if(boardChessCondition(row + i, col + i) == noChess)
                return true;
            else if(boardChessCondition(row + i, col + i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row - i, col + i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row + i, col - i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row - i, col - i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
        }

        return false;
    }
    else if(board[row][col].chessType == "Queen")
    {
        //up
        for(int i = 1;i<8;i++)
        {
            if(!ifPosInBoard(row + i, col))
                break;

            if(boardChessCondition(row + i, col) == noChess)
                return true;
            else if(boardChessCondition(row + i, col) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row - i, col) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row, col + i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row, col - i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row + i, col + i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row - i, col + i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row + i, col - i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
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
                return true;
            else if(boardChessCondition(row - i, col - i) == whiteChess)
            {
                if(board[row][col].player == 'w')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
            else//boardChessCondition == blackChess
            {
                if(board[row][col].player == 'b')
                {
                    break;
                }
                else
                {
                    return true;
                    break;
                }
            }
        }

        return false;
    }
    else if(board[row][col].chessType == "King")
    {
        if(board[row][col].player == 'w')
        {

            //up
            if(ifPosInBoard(row + 1, col) && boardChessCondition(row + 1, col) != whiteChess && board[row + 1][col].bTarget == 0)
                return true;

            //down
            if(ifPosInBoard(row - 1, col) && boardChessCondition(row - 1, col) != whiteChess && board[row - 1][col].bTarget == 0)
                return true;

            //right
            if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) != whiteChess && board[row][col + 1].bTarget == 0)
                return true;

            //left
            if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) != whiteChess && board[row][col - 1].bTarget == 0)
                return true;

            //up right
            if(ifPosInBoard(row + 1, col + 1) && boardChessCondition(row + 1, col + 1) != whiteChess && board[row + 1][col + 1].bTarget == 0)
                return true;

            //up left
            if(ifPosInBoard(row + 1, col - 1) && boardChessCondition(row + 1, col - 1) != whiteChess && board[row + 1][col - 1].bTarget == 0)
                return true;

            //down right
            if(ifPosInBoard(row - 1, col + 1) && boardChessCondition(row - 1, col + 1) != whiteChess && board[row - 1][col + 1].bTarget == 0)
                return true;

            //down left
            if(ifPosInBoard(row - 1, col - 1) && boardChessCondition(row - 1, col - 1) != whiteChess && board[row - 1][col - 1].bTarget == 0)
                return true;

            //left castle
            if(White.king.ifMove == false && White.rooks[board[7][0].index].ifMove == false && board[7][0].chessType == "Rook" && board[7][0].player == 'w')
            {
                if(board[7][1].ifHavePiece == false && board[7][2].ifHavePiece == false && board[7][3].ifHavePiece == false)
                {
                    if(board[7][4].bTarget == 0 && board[7][1].bTarget == 0 && board[7][2].bTarget == 0 && board[7][3].bTarget == 0)
                    {
                        return true;
                    }
                }
            }

            //right castle
            if(White.king.ifMove == false && White.rooks[board[7][7].index].ifMove == false && board[7][7].chessType == "Rook" && board[7][7].player == 'w')
            {
                if(board[7][5].ifHavePiece == false && board[7][6].ifHavePiece == false)
                {
                    if(board[7][4].bTarget == 0 && board[7][5].bTarget == 0 && board[7][6].bTarget == 0)
                    {
                        return true;
                    }
                }
            }

            return false;
        }
        else//board[row][col].player = 'b'
        {
            //up
            if(ifPosInBoard(row + 1, col) && boardChessCondition(row + 1, col) != blackChess && board[row + 1][col].wTarget == 0)
                return true;

            //down
            if(ifPosInBoard(row - 1, col) && boardChessCondition(row - 1, col) != blackChess && board[row - 1][col].wTarget == 0)
                return true;

            //right
            if(ifPosInBoard(row, col + 1) && boardChessCondition(row, col + 1) != blackChess && board[row][col + 1].wTarget == 0)
                return true;

            //left
            if(ifPosInBoard(row, col - 1) && boardChessCondition(row, col - 1) != blackChess && board[row][col - 1].wTarget == 0)
                return true;

            //up right
            if(ifPosInBoard(row + 1, col + 1) && boardChessCondition(row + 1, col + 1) != blackChess && board[row + 1][col + 1].wTarget == 0)
                return true;

            //up left
            if(ifPosInBoard(row + 1, col - 1) && boardChessCondition(row + 1, col - 1) != blackChess && board[row + 1][col - 1].wTarget == 0)
                return true;

            //down right
            if(ifPosInBoard(row - 1, col + 1) && boardChessCondition(row - 1, col + 1) != blackChess && board[row - 1][col + 1].wTarget == 0)
                return true;

            //down left
            if(ifPosInBoard(row - 1, col - 1) && boardChessCondition(row - 1, col - 1) != blackChess && board[row - 1][col - 1].wTarget == 0)
                return true;

            //left castle
            if(Black.king.ifMove == false && Black.rooks[board[0][0].index].ifMove == false && board[0][0].chessType == "Rook" && board[0][0].player == 'b')
            {
                if(board[0][1].ifHavePiece == false && board[0][2].ifHavePiece == false && board[0][3].ifHavePiece == false)
                {
                    if(board[0][4].wTarget == 0 && board[0][1].wTarget == 0 && board[0][2].wTarget == 0 && board[0][3].wTarget == 0)
                    {
                        return true;
                    }
                }
            }

            //right castle
            if(Black.king.ifMove == false && Black.rooks[board[0][7].index].ifMove == false && board[0][7].chessType == "Rook" && board[0][7].player == 'b')
            {
                if(board[0][5].ifHavePiece == false && board[0][6].ifHavePiece == false)
                {
                    if(board[0][4].wTarget == 0 && board[0][5].wTarget == 0 && board[0][6].wTarget == 0)
                    {
                        return true;
                    }
                }
            }

            return false;
        }
    }
}

//intent: transform board into fen encoding
//pre: none
//post: store the fen-encode board into fen vector
void GameManager::transBoardToFen()
{
    int blank = 0;
    fen = "";

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(board[i][j].ifHavePiece == false)
            {
                blank++;
            }
            else//board[i][j].ifHavePiece == true
            {
                if(blank != 0)
                {
                    fen.push_back(blank + '0');
                    blank = 0;
                }

                if(board[i][j].player == 'b')
                {
                    if(board[i][j].chessType == "Pawn")
                    {
                        fen.push_back(blank + 'p');
                    }
                    else if(board[i][j].chessType == "Rook")
                    {
                        fen.push_back(blank + 'r');
                    }
                    else if(board[i][j].chessType == "Knight")
                    {
                        fen.push_back(blank + 'n');
                    }
                    else if(board[i][j].chessType == "Bishop")
                    {
                        fen.push_back(blank + 'b');
                    }
                    else if(board[i][j].chessType == "Queen")
                    {
                        fen.push_back(blank + 'q');
                    }
                    else if(board[i][j].chessType == "King")
                    {
                        fen.push_back(blank + 'k');
                    }
                }
                else//board[i][j].player == 'w'
                {
                    if(board[i][j].chessType == "Pawn")
                    {
                        fen.push_back(blank + 'P');
                    }
                    else if(board[i][j].chessType == "Rook")
                    {
                        fen.push_back(blank + 'R');
                    }
                    else if(board[i][j].chessType == "Knight")
                    {
                        fen.push_back(blank + 'N');
                    }
                    else if(board[i][j].chessType == "Bishop")
                    {
                        fen.push_back(blank + 'B');
                    }
                    else if(board[i][j].chessType == "Queen")
                    {
                        fen.push_back(blank + 'Q');
                    }
                    else if(board[i][j].chessType == "King")
                    {
                        fen.push_back(blank + 'K');
                    }
                }
            }
        }

        if(blank != 0)
        {
            fen.push_back(blank + '0');
            blank = 0;
        }

        if(i != 7)
            fen.push_back('/');
    }
}

//intent: check if same board repeated 3 times
//pre: none
//post: return if board repeaed 3 times
void GameManager::IfBoardRepeat3Times(string curFen)
{
    int repeatTimes = 0;

    for(int i = 0; i < fens.size(); i++)
    {
        if(curFen == fens[i])
        {
            repeatTimes++;
        }

        if(repeatTimes == 3)
        {
            ifDraw = true;
            return;
        }
    }
}

//intent: check if insufficient chess piece
//pre: none
//post: game draw
void GameManager::ifInsufficientChess()//The only player left is the king
{
    if(bPawn > 0 || bQueen > 0 || bRook > 0 || bBishop >= 2 || (bKnight > 0 && bBishop > 0) ||
        wPawn > 0 || wQueen > 0 || wRook > 0 || wBishop >= 2 || (wKnight > 0 && wBishop > 0))
    {
        return;
    }

    ifDraw = true;
}

//intent: promote pawn if reach other end
//pre: pawn reach other end
//post pawn promoted
void GameManager::Promoting(int row, int col, string type)
{
    //see which type is chosen and switch the pawn into new chess piece
    if(type == "Queen")
    {
        Queen *newQueen = new Queen;

        if(board[row][col].player == 'w')
        {
            White.pawns[board[row][col].index].ifPromoting = true;
            White.pawns[board[row][col].index].promotingType = "Queen";
            newQueen->player = 'w';
            newQueen->x = col;
            newQueen->y = row;
            White.queens.push_back(*newQueen);
            board[row][col].chessType = "Queen";
            board[row][col].ifHavePiece = true;
            board[row][col].player = 'w';
            board[row][col].index = White.queens.size() - 1;
        }
        else//board[row][col].player == 'b'
        {
            Black.pawns[board[row][col].index].ifPromoting = true;
            Black.pawns[board[row][col].index].promotingType = "Queen";
            newQueen->player = 'b';
            newQueen->x = col;
            newQueen->y = row;
            Black.queens.push_back(*newQueen);
            board[row][col].chessType = "Queen";
            board[row][col].ifHavePiece = true;
            board[row][col].player = 'b';
            board[row][col].index = Black.queens.size() - 1;
        }
    }
    else if(type == "Bishop")
    {
        Bishop *newBishop = new Bishop;

        if(board[row][col].player == 'w')
        {
            White.pawns[board[row][col].index].ifPromoting = true;
            White.pawns[board[row][col].index].promotingType = "Bishop";
            newBishop->player = 'w';
            newBishop->x = col;
            newBishop->y = row;
            White.bishops.push_back(*newBishop);
            board[row][col].chessType = "Bishop";
            board[row][col].ifHavePiece = true;
            board[row][col].player = 'w';
            board[row][col].index = White.bishops.size() - 1;
        }
        else//board[row][col].player == 'b'
        {
            Black.pawns[board[row][col].index].ifPromoting = true;
            Black.pawns[board[row][col].index].promotingType = "Bishop";
            newBishop->player = 'b';
            newBishop->x = col;
            newBishop->y = row;
            Black.bishops.push_back(*newBishop);
            board[row][col].chessType = "Bishop";
            board[row][col].ifHavePiece = true;
            board[row][col].player = 'b';
            board[row][col].index = Black.bishops.size() - 1;
        }
    }
    else if(type == "Knight")
    {
        Knight *newKnight = new Knight;

        if(board[row][col].player == 'w')
        {
            White.pawns[board[row][col].index].ifPromoting = true;
            White.pawns[board[row][col].index].promotingType = "Knight";
            newKnight->player = 'w';
            newKnight->x = col;
            newKnight->y = row;
            White.knights.push_back(*newKnight);
            board[row][col].chessType = "Knight";
            board[row][col].ifHavePiece = true;
            board[row][col].player = 'w';
            board[row][col].index = White.knights.size() - 1;
        }
        else//board[row][col].player == 'b'
        {
            Black.pawns[board[row][col].index].ifPromoting = true;
            Black.pawns[board[row][col].index].promotingType = "Knight";
            newKnight->player = 'b';
            newKnight->x = col;
            newKnight->y = row;
            Black.knights.push_back(*newKnight);
            board[row][col].chessType = "Knight";
            board[row][col].ifHavePiece = true;
            board[row][col].player = 'b';
            board[row][col].index = Black.knights.size() - 1;
        }
    }
    else if(type == "Rook")
    {
        Rook *newRook = new Rook;

        if(board[row][col].player == 'w')
        {
            White.pawns[board[row][col].index].ifPromoting = true;
            White.pawns[board[row][col].index].promotingType = "Rook";
            newRook->player = 'w';
            newRook->x = col;
            newRook->y = row;
            White.rooks.push_back(*newRook);
            board[row][col].chessType = "Rook";
            board[row][col].ifHavePiece = true;
            board[row][col].player = 'w';
            board[row][col].index = White.rooks.size() - 1;
        }
        else//board[row][col].player == 'b'
        {
            Black.pawns[board[row][col].index].ifPromoting = true;
            Black.pawns[board[row][col].index].promotingType = "Rook";
            newRook->player = 'b';
            newRook->x = col;
            newRook->y = row;
            Black.rooks.push_back(*newRook);
            board[row][col].chessType = "Rook";
            board[row][col].ifHavePiece = true;
            board[row][col].player = 'b';
            board[row][col].index = Black.rooks.size() - 1;
        }
    }

    board[row][col].chessType = type;
    computeChessNumber();
}

//intent: judge special case of in sufficient chess piece
//pre: none
//post: check if draw
void GameManager::judgeSpecialCase(int wBishop, int bBishop)
{
    if(wBishop == 2 && bBishop == 2)
    {
        int wFirstBishop = -1, wSecondBishop = -1, bFirstBishop = -1, bSecondBishop = -1;

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(board[i][j].ifHavePiece && board[i][j].player == 'w' && board[i][j].chessType == "Bishop")
                {
                    if(wFirstBishop == -1)
                    {
                        wFirstBishop = i + j;
                    }
                    else
                    {
                        wSecondBishop = i + j;
                    }
                }
                else if(board[i][j].ifHavePiece && board[i][j].player == 'b' && board[i][j].chessType == "Bishop")
                {
                    if(bFirstBishop == -1)
                    {
                        bFirstBishop = i + j;
                    }
                    else
                    {
                        bSecondBishop = i + j;
                    }
                }
            }
        }

        if(wFirstBishop % 2 == wSecondBishop % 2 && bFirstBishop % 2 == bSecondBishop % 2)
        {
            ifDraw = true;
        }
    }
    else
    {
        int FirstBishop = -1, SecondBishop = -1;

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(board[i][j].ifHavePiece && board[i][j].chessType == "Bishop")
                {
                    if(FirstBishop == -1)
                    {
                        FirstBishop = i + j;
                    }
                    else
                    {
                        SecondBishop = i + j;
                    }
                }
            }
        }

        if(FirstBishop % 2 == SecondBishop % 2)
        {
            ifDraw = true;
        }
    }
}

//intent: compute number of each type of chess pieces on board
//pre: board initialized
//post: store the computed values
void GameManager::computeChessNumber()
{
    wPawn = 0;
    wRook = 0;
    wKnight = 0;
    wBishop = 0;
    wQueen = 0;
    bPawn = 0;
    bRook = 0;
    bKnight = 0;
    bBishop = 0;
    bQueen = 0;

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            board[row][col].canMove = false;

            if(board[row][col].ifHavePiece)
            {
                if(board[row][col].player == 'w')
                {
                    if(board[row][col].chessType == "Pawn")
                    {
                        wPawn++;
                    }
                    else if(board[row][col].chessType == "Rook")
                    {
                        wRook++;
                    }
                    else if(board[row][col].chessType == "Knight")
                    {
                        wKnight++;
                    }
                    else if(board[row][col].chessType == "Bishop")
                    {
                        wBishop++;
                    }
                    else if(board[row][col].chessType == "Queen")
                    {
                        wQueen++;
                    }
                }
                else//board[row][col].player == 'b'
                {
                    if(board[row][col].chessType == "Pawn")
                    {
                        bPawn++;
                    }
                    else if(board[row][col].chessType == "Rook")
                    {
                        bRook++;
                    }
                    else if(board[row][col].chessType == "Knight")
                    {
                        bKnight++;
                    }
                    else if(board[row][col].chessType == "Bishop")
                    {
                        bBishop++;
                    }
                    else if(board[row][col].chessType == "Queen")
                    {
                        bQueen++;
                    }
                }
            }
        }
    }

    if(wPawn == 0 && wRook == 0 && wKnight == 0 && wQueen == 0 && bBishop == 1
        && bPawn == 0 && bRook == 0 && bKnight == 0 && bQueen == 0 && wBishop == 1)
        ifDraw = true;
    else if(wPawn == 0 && wRook == 0 && wKnight == 0 && wQueen == 0 && bBishop == 2
             && bPawn == 0 && bRook == 0 && bKnight == 0 && bQueen == 0 && wBishop == 2)
        judgeSpecialCase(2, 2);
    else if(wPawn == 0 && wRook == 0 && wKnight == 0 && wQueen == 0 && bBishop == 0
             && bPawn == 0 && bRook == 0 && bKnight == 0 && bQueen == 0 && wBishop == 2)
        judgeSpecialCase(2, 0);
    else if(wPawn == 0 && wRook == 0 && wKnight == 0 && wQueen == 0 && bBishop == 2
             && bPawn == 0 && bRook == 0 && bKnight == 0 && bQueen == 0 && wBishop == 0)
        judgeSpecialCase(0, 2);
}
