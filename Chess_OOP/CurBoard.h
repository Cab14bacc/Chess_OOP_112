#include "saveAllInformation.h".h"
#ifndef CURBOARD_H
#define CURBOARD_H
class CurBoard
{
public:
    SaveAllInformation curBoard[8][8];//save all information
    char playerTurn = 'w';// save who play this turn
    bool ifWhiteKingMove = false;//save if white king have been moved
    bool ifBlackKingMove = false;//save if black king have been moved
};

#endif // CURBOARD_H
