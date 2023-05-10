
#ifndef PAWN_H
#define PAWN_H
class Pawn
{
public:
    char player;//while:w, black:b
    int x;
    int y;
    void setPlayer(char play);
    void setPos(int posX,int posY);
};
#endif // PAWN_H
