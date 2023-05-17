#include "saveAllInformation.h"
#ifndef CURBOARD_H
#define CURBOARD_H
class CurBoard
{
public:
    SaveAllInformation curBoard[8][8];
    char playerTurn = 'w';
};

#endif // CURBOARD_H
