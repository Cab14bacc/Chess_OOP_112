#include "myLabel.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void labelClicked();

    void on_newGame_clicked();

private:
    Ui::MainWindow *ui;
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
};

#endif // MAINWINDOW_H
