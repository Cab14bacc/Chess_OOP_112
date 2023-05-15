
#ifndef PAWN_H
#define PAWN_H
class Pawn
{
public:
    char player;//while:w, black:b
    int x;
    int y;
    int index;
    bool ifmove2Step = false;
    bool inNextTurn = false;
};
#endif // PAWN_H
