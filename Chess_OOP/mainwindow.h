#include "myLabel.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSound>
#include "promomenu.h"

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

    void setBoard();

    void split(string Words[], QString Name);

    void initIcon();

    void update();

    void printInformation();

    void loadBoard();

    void setTime();

    void setSound();

    void showResultWindow(int whoWin);

    void resetGame();

private slots:
    void labelClicked();

    void on_newGame_clicked();

    void on_undo_clicked();

    void on_redo_clicked();

    void updateTimer();

private:
    Ui::MainWindow *ui;
    PromoMenu promoMenuW;
    PromoMenu promoMenuB;
    QList<MyLabel*> labelList;
    MyLabel *label;
    QPixmap *iconWKing;
    QPixmap *iconWQueen;
    QPixmap *iconWBishop;
    QPixmap *iconWKnight;
    QPixmap *iconWRook;
    QPixmap *iconWPawn;
    QPixmap *iconBKing;
    QPixmap *iconBQueen;
    QPixmap *iconBBishop;
    QPixmap *iconBKnight;
    QPixmap *iconBRook;
    QPixmap *iconBPawn;
    QTimer *whiteTimer = new QTimer;
    QTimer *blackTimer = new QTimer;
    int whiteCounter;
    int blackCounter;
    QSound *startSound;
    QSound *clickSound;
};

#endif // MAINWINDOW_H
