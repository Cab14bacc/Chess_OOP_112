#include <iostream>
#ifndef PLAYERMOVE_H
#define PLAYERMOVE_H

using namespace std;

class PlayerMove{

public:
    char chessPlayer = '0';
    string chessType = "0";
    int originalPos[2] = {0};//row, col
    int afterPos[2] = {0};//row, col
};

#endif // PLAYERMOVE_H
