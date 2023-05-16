#include "Player.h"
#include "viewmanager.h"
#include "CurBoard.h"
#include <vector>

using namespace std;

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#define whiteChess 1
#define blackChess 2
#define noChess 3
#define whiteWin 1
#define blackWin 2
#define gameContinue 3
#define draw 4

class GameManager
{
public:
    GameManager();
    int wPawn;
    int wRook;
    int wKnight;
    int wBishop;
    int wQueen;
    int bPawn;
    int bRook;
    int bKnight;
    int bBishop;
    int bQueen;
    int noEat;
    string fen;
    vector <string> fens;
    bool ifWhiteCanMove;
    bool ifBlackCanMove;
    bool ifDraw;
    int curStep;
    CurBoard curBoard;
    vector <CurBoard> steps;
    Player White;
    Player Black;
    ViewManager board[8][8];
    int clickTimes;
    char playerTurn;
    char selectChessPlayer;
    string selectChessType;
    int selectChessIndex;
    void showCanMove(int row, int col);
    void playerMove(int row, int col);
    bool ifPosInBoard(int row, int col);
    int boardChessCondition(int row, int col);//return 1:white chess、2:black、3:no chess on the board
    void eraseChessPiece(string chessType, char player,int index);
    void computeTarget();
    void recordCurBoard();
    int judgeWinOrLose();
    void judgeIfPlayerCanMove();
    void transBoardToFen();
    void IfBoardRepeat3Times(string curFen);
    void ifInsufficientChess(char player);
};

#endif // GAMEMANAGER_H
