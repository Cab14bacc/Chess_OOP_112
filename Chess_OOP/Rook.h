
#ifndef ROOK_H
#define ROOK_H
class Rook{
public:
    char player;//while:w, black:b
    int x;
    int y;
    void setPlayer(char play);
    void setPos(int posX,int posY);
};
#endif // ROOK_H
