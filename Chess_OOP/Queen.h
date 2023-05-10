
#ifndef QUEEN_H
#define QUEEN_H
class Queen
{
public:
    char player;//while:w, black:b
    int x;
    int y;
    void setPlayer(char play);
    void setPos(int posX,int posY);
};
#endif // QUEEN_H
