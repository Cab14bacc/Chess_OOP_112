
#ifndef KNIGHT_H
#define KNIGHT_H
class Knight
{
public:
    char player;//while:w, black:b
    int x;
    int y;
    void setPlayer(char play);
    void setPos(int posX,int posY);
    void move();
};
#endif // KNIGHT_H
