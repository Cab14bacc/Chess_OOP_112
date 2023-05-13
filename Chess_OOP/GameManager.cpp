
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

    if(board[row][col].ifHavePiece && board[row][col].player != selectChessPlayer)
    {
        eraseChessPiece(board[row][col].chessType,board[row][col].player,board[row][col].index);
    }

    if(selectChessPlayer == 'w')
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
        else if(selectChessType == "King")
        {
            if(board[row][col].chessType == "Rook" && board[row][col].player == 'w')
            {


            }
            board[White.king.y][White.king.x].index = 0;
            board[White.king.y][White.king.x].chessType = "0";
            board[White.king.y][White.king.x].ifHavePiece = false;
            board[White.king.y][White.king.x].player = '0';
            White.king.y = row;
            White.king.x = col;
        }
        board[row][col].chessType = selectChessType;
        board[row][col].index = selectChessIndex;
        board[row][col].ifHavePiece = true;
        board[row][col].player = selectChessPlayer;
    }
    else if(selectChessPlayer == 'b')
    {
        if(selectChessType == "King")
        {
            if(board[row][col].chessType == "Rook" && board[row][col].player == 'b')
            {
                if(White.king.x - White.rooks[board[row][col].index].x > 0)
                {
                    board[White.king.y][White.king.x].index = 0;
                    board[White.king.y][White.king.x].chessType = "0";
                    board[White.king.y][White.king.x].ifHavePiece = false;
                    board[White.king.y][White.king.x].player = '0';
                    board[White.king.y][White.king.x - 2].chessType = selectChessType;
                    board[White.king.y][White.king.x - 2].index = selectChessIndex;
                    board[White.king.y][White.king.x - 2].ifHavePiece = true;
                    board[White.king.y][White.king.x - 2].player = selectChessPlayer;

                    board[White.king.y][White.king.x - 2].chessType = selectChessType;
                    board[White.king.y][White.king.x - 2].index = selectChessIndex;
                    board[White.king.y][White.king.x - 2].ifHavePiece = true;
                    board[White.king.y][White.king.x - 2].player = selectChessPlayer;
                }
                else
                {


                }
                board[row][col].chessType = "0";
                board[row][col].index = 0;
                board[row][col].ifHavePiece = false;
                board[row][col].player = '0';

            }
            else
            {
                board[White.king.y][White.king.x].index = 0;
                board[White.king.y][White.king.x].chessType = "0";
                board[White.king.y][White.king.x].ifHavePiece = false;
                board[White.king.y][White.king.x].player = '0';
                Black.king.y = row;
                Black.king.x = col;

            }

        }
        else
        {
            if(selectChessType == "Pawn")
            {
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].index = 0;
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].chessType = "0";
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].ifHavePiece = false;
                board[White.pawns[selectChessIndex].y][White.pawns[selectChessIndex].x].player = '0';
                Black.pawns[selectChessIndex].y = row;
                Black.pawns[selectChessIndex].x = col;
            }
            else if(selectChessType == "Rook")
            {
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].index = 0;
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].chessType = "0";
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].ifHavePiece = false;
                board[White.rooks[selectChessIndex].y][White.rooks[selectChessIndex].x].player = '0';
                Black.rooks[selectChessIndex].y = row;
                Black.rooks[selectChessIndex].x = col;
            }
            else if(selectChessType == "Bishop")
            {
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].index = 0;
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].chessType = "0";
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].ifHavePiece = false;
                board[White.bishops[selectChessIndex].y][White.bishops[selectChessIndex].x].player = '0';
                Black.bishops[selectChessIndex].y = row;
                Black.bishops[selectChessIndex].x = col;
            }
            else if(selectChessType == "Knight")
            {
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].index = 0;
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].chessType = "0";
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].ifHavePiece = false;
                board[White.knights[selectChessIndex].y][White.knights[selectChessIndex].x].player = '0';
                Black.knights[selectChessIndex].y = row;
                Black.knights[selectChessIndex].x = col;
            }
            else if(selectChessType == "Queen")
            {
                board[White.queens[selectChessIndex].y][White.queens[selectChessIndex].x].index = 0;
                board[White.queens[selectChessIndex].y][White.queens[selectChessIndex].x].chessType = "0";
                board[White.queens[selectChessIndex].y][White.queens[selectChessIndex].x].ifHavePiece = false;
                board[White.queens[selectChessIndex].y][White.queens[selectChessIndex].x].player = '0';
                Black.queens[selectChessIndex].y = row;
                Black.queens[selectChessIndex].x = col;
            }
            board[row][col].chessType = selectChessType;
            board[row][col].index = selectChessIndex;
            board[row][col].ifHavePiece = true;
            board[row][col].player = selectChessPlayer;

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
