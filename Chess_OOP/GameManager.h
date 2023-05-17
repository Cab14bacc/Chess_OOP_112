#include "Player.h"
#include "viewmanager.h"
#include "CurBoard.h"
#include <vector>
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"

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
    int wPawn;//how many white pawn
    int wRook;//how many white rook
    int wKnight;//how many white knight
    int wBishop;//how many white bishop
    int wQueen;//how many white queen
    int bPawn;//how many black pawn
    int bRook;//how many black rook
    int bKnight;//how many black knight
    int bBishop;//how many black bishop
    int bQueen;//how many black queen
    int noEat;//how many turns no eat any chess
    string fen;//this turn's FEN
    vector <string> fens;//all FENs
    bool ifWhiteCanMove;//save if White can move
    bool ifBlackCanMove;//save if Black can move
    bool ifDraw;//save if Draw
    int curStep;//save current step
    CurBoard curBoard;//save current board
    vector <CurBoard> steps;//save all board
    Player White;
    Player Black;
    ViewManager board[8][8];//save board information
    int clickTimes;//save the times player clicked ui
    char playerTurn;//save which player playing
    char selectChessPlayer;//the select Chess belong to which player
    string selectChessType;//the select Chess type
    int selectChessIndex;////the select Chess index
    int blackKingBeenAttackBy[2];//save the chess can attack black king pos
    int whiteKingBeenAttackBy[2];//save the chess can attack white king pos
    void showCanMove(int row, int col);//compute where can move
    void playerMove(int row, int col);//execute move
    bool ifPosInBoard(int row, int col);//if input pos in baord
    int boardChessCondition(int row, int col);//return 1:white chess、2:black、3:no chess on the board
    void computeTarget();//compute every pos can be how many chess attack
    void recordCurBoard();//record currend board
    int judgeWinOrLose();//judge if checkmate
    bool ifPosCanMove(int row, int col);//if chess in this pos can move
    void judgeIfPlayerCanMove(char player);//judge if input player can move
    void transBoardToFen();//translate board information to FEN type
    void IfBoardRepeat3Times(string curFen);//check if the same board appear 3 times
    void ifInsufficientChess();//check if have sufficient chess to checkmate
    void Promoting(int row, int col, string type);//Promoting
    void judgeSpecialCase(int wBishop, int bBishop);//check if have sufficient chess to checkmate(special case)
    void computeChessNumber();//compute how many chess on board, and save into their type
    void eraseChessPiece(string chessType, char player,int index); // reset noEat
};

#endif // GAMEMANAGER_H
