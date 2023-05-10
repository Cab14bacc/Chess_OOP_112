
#ifndef BISHOP_H
#define BISHOP_H

class Bishop
{
public:
    char player;//while:w, black:b
    int x;
    int y;
    void setPlayer(char play);
    void setPos(int posX,int posY);
};

#endif // BISHOP_H
