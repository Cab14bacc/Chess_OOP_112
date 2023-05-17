
#ifndef ROOK_H
#define ROOK_H
class Rook
{
public:
    char player;//while:w, black:b
    int x;//save pos x
    int y;//save pos y
    int index;//save index
    bool ifMove = false;//if rook have been moved
};
#endif // ROOK_H
