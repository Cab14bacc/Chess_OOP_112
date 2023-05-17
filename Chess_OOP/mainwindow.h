#include "myLabel.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSound>

using namespace std;;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setBoard();//set board

    void split(string Words[], QString Name);//to split Qbject name

    void initIcon();//initialize all icons

    void update();//update ui

    void printInformation();//print information to debug

    void loadBoard();//load board from steps

    void setTime();//set time

    void setSound();//set sound

    void showResultWindow(int whoWin);//if game, show result

    void resetGame();//reset game

    void Promoting(int row, int col);//Promoting

    void shoeWhoFirst();//let player choose who first

private slots:
    void labelClicked();//if board be clicked, call this function

    void on_newGame_clicked();//start new game

    void on_undo_clicked();//undo

    void on_redo_clicked();//redo

    void updateTimer();//update time

    void on_Resign_clicked();//resign

private:
    Ui::MainWindow *ui;
    QList<MyLabel*> labelList;//save label
    MyLabel *label;//creat new label
    QPixmap *iconWKing;//white king icon
    QPixmap *iconWQueen;//white queen icon
    QPixmap *iconWBishop;//white bishop icon
    QPixmap *iconWKnight;//white knight icon
    QPixmap *iconWRook;//white rook icon
    QPixmap *iconWPawn;//white pawn icon
    QPixmap *iconBKing;//black king icon
    QPixmap *iconBQueen;//black queen icon
    QPixmap *iconBBishop;//black bishop icon
    QPixmap *iconBKnight;//black knight icon
    QPixmap *iconBRook;//black rook icon
    QPixmap *iconBPawn;//black pawn icon
    QTimer whiteTimer;//white time
    QTimer blackTimer;//black time
    int whiteCounter;//white have second
    int blackCounter;//black have second
    QSound *startSound;//BGM
    QSound *clickSound;
};

#endif // MAINWINDOW_H
