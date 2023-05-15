#include "GameManager.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include <iostream>
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"

using namespace std;

//global value
GameManager game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setBoard();//set labels and put color on it
    initIcon();//just to set images
}

MainWindow::~MainWindow()
{
    delete ui;
}

//set label and put color on it
void MainWindow::setBoard()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            label = new MyLabel(this);
            label->setParent(this);
            label->setFixedSize(60,60);
            label->setText("");

            if((i + j) % 2 == 0)
            {
                label->setStyleSheet("QLabel{background-color:rgb(224,224,198);}");
            }
            else
            {
                label->setStyleSheet("QLabel{background-color:rgb(118,150,86);}");
            }

            label->show();
            ui->gameBoard->addWidget(label,i,j);
            label->setObjectName(QString::number(i) + " " + QString::number(j));
            labelList.append(label);
            QObject::connect(label ,SIGNAL(signalclicked()),this,SLOT(labelClicked()));
        }
    }
}

//if label clicled, call this function
void MainWindow::labelClicked()
{
    MyLabel *lab = qobject_cast<MyLabel*>(sender());
    QString Name = lab->objectName();
    string words[2];
    split(words,Name);
    int curRow = stoi(words[0]);
    int curCol = stoi(words[1]);

    if(game.clickTimes == 1)
    {
        game.showCanMove(curRow, curCol);
        printInformation();
        update();
    }
    else
    {
        game.playerMove(curRow, curCol);
        game.computeTarget();
        printInformation();
        game.clickTimes = 1;
        update();
    }
}

void MainWindow::update()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            MyLabel *lab;
            QString row = QString::number(i);
            QString col = QString::number(j);
            lab = this->findChild<MyLabel*>(row + " " + col);

            if(game.board[i][j].canMove)
            {
                lab->setStyleSheet("QLabel{background-color:rgb(255,253,85);}");
            }
            else
            {
                if((i + j) % 2 == 0)
                {
                    lab->setStyleSheet("QLabel{background-color:rgb(224,224,198);}");
                }
                else
                {
                    lab->setStyleSheet("QLabel{background-color:rgb(118,150,86);}");
                }
            }

            if(game.board[i][j].ifHavePiece)
            {
                if(game.board[i][j].player == 'w')
                {
                    if(game.board[i][j].chessType == "Pawn")
                        lab->setPixmap(*iconWPawn);
                    else if(game.board[i][j].chessType == "Rook")
                        lab->setPixmap(*iconWRook);
                    else if(game.board[i][j].chessType == "Knight")
                        lab->setPixmap(*iconWKnight);
                    else if(game.board[i][j].chessType == "Bishop")
                        lab->setPixmap(*iconWBishop);
                    else if(game.board[i][j].chessType == "Queen")
                        lab->setPixmap(*iconWQueen);
                    else if(game.board[i][j].chessType == "King")
                        lab->setPixmap(*iconWKing);
                }
                else//game.board[i][j].player == 'b'
                {
                    if(game.board[i][j].chessType == "Pawn")
                        lab->setPixmap(*iconBPawn);
                    else if(game.board[i][j].chessType == "Rook")
                        lab->setPixmap(*iconBRook);
                    else if(game.board[i][j].chessType == "Knight")
                        lab->setPixmap(*iconBKnight);
                    else if(game.board[i][j].chessType == "Bishop")
                        lab->setPixmap(*iconBBishop);
                    else if(game.board[i][j].chessType == "Queen")
                        lab->setPixmap(*iconBQueen);
                    else if(game.board[i][j].chessType == "King")
                        lab->setPixmap(*iconBKing);
                }
            }
            else
            {
                lab->clear();
            }
        }
    }
}

// can ignore this temporary
void MainWindow::split(string Words[], QString Name)
{
    string strName = Name.toStdString();
    stringstream ss(strName);
    string temp;
    int N = 0;
    while (getline(ss, temp, ' ')) {
        Words[N] = temp;
        N++;
    }
}

//if new game button clicked, put images and call gamestart function
void MainWindow::on_newGame_clicked()
{
    game.playerTurn = 'w';
    game.Black.pawns.clear();
    game.Black.rooks.clear();
    game.Black.knights.clear();
    game.Black.bishops.clear();
    game.Black.queens.clear();
    game.White.pawns.clear();
    game.White.rooks.clear();
    game.White.knights.clear();
    game.White.bishops.clear();
    game.White.queens.clear();

    for(int i =0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            game.board[i][j].ifHavePiece = false;
            game.board[i][j].wTarget = 0;
            game.board[i][j].bTarget = 0;
            game.board[i][j].player = '0';
            game.board[i][j].chessType = "0";
            game.board[i][j].index = 0;
            game.board[i][j].canMove = false;
        }
    }

    update();

    QString row;
    QString col;
    MyLabel *lab;
    King *newKing;
    Queen *newQueen = new Queen;
    Bishop *newBishop = new Bishop;
    Knight *newKnight = new Knight;
    Rook *newRook = new Rook;
    Pawn *newPawn = new Pawn;

    for(int i = 0; i < 8; i++)
    {
        //newPawn = new Pawn;
        row = QString::number(1);
        col = QString::number(i);
        lab = this->findChild<MyLabel*>(row + " " + col);
        lab->setPixmap(*iconBPawn);
        newPawn->x = i;
        newPawn->y = 1;
        game.Black.pawns.push_back(*newPawn);
        game.board[1][i].player = 'b';
        game.board[1][i].chessType = "Pawn";
        game.board[1][i].ifHavePiece = true;
        game.board[1][i].index = i;
        //newPawn = new Pawn;
        row = QString::number(6);
        col = QString::number(i);
        lab = this->findChild<MyLabel*>(row + " " + col);
        lab->setPixmap(*iconWPawn);
        newPawn->x = i;
        newPawn->y = 6;
        game.White.pawns.push_back(*newPawn);
        game.board[6][i].player = 'w';
        game.board[6][i].chessType = "Pawn";
        game.board[6][i].ifHavePiece = true;
        game.board[6][i].index = i;
    }

    //set black rook
    //newRook = new Rook;
    row = QString::number(0);
    col = QString::number(0);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconBRook);
    newRook->x = 0;
    newRook->y = 0;
    game.Black.rooks.push_back(*newRook);
    game.board[0][0].player = 'b';
    game.board[0][0].chessType = "Rook";
    game.board[0][0].ifHavePiece = true;
    game.board[0][0].index = 0;
    //newRook = new Rook;
    row = QString::number(0);
    col = QString::number(7);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconBRook);
    newRook->x = 7;
    newRook->y = 0;
    game.Black.rooks.push_back(*newRook);
    game.board[0][7].player = 'b';
    game.board[0][7].chessType = "Rook";
    game.board[0][7].ifHavePiece = true;
    game.board[0][7].index = 1;

    //set black Knight
    //newKnight = new Knight;
    row = QString::number(0);
    col = QString::number(1);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconBKnight);
    newKnight->x = 1;
    newKnight->y = 0;
    game.Black.knights.push_back(*newKnight);
    game.board[0][1].player = 'b';
    game.board[0][1].chessType = "Knight";
    game.board[0][1].ifHavePiece = true;
    game.board[0][1].index = 0;
    //newKnight = new Knight;
    row = QString::number(0);
    col = QString::number(6);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconBKnight);
    newKnight->x = 6;
    newKnight->y = 0;
    game.Black.knights.push_back(*newKnight);
    game.board[0][6].player = 'b';
    game.board[0][6].chessType = "Knight";
    game.board[0][6].ifHavePiece = true;
    game.board[0][6].index = 1;

    //set black Bishop
    //newBishop = new Bishop;
    row = QString::number(0);
    col = QString::number(2);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconBBishop);
    newBishop->x = 2;
    newBishop->y = 0;
    game.Black.bishops.push_back(*newBishop);
    game.board[0][2].player = 'b';
    game.board[0][2].chessType = "Bishop";
    game.board[0][2].ifHavePiece = true;
    game.board[0][2].index = 0;
    //newBishop = new Bishop;
    row = QString::number(0);
    col = QString::number(5);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconBBishop);
    newBishop->x = 5;
    newBishop->y = 0;
    game.Black.bishops.push_back(*newBishop);
    game.board[0][5].player = 'b';
    game.board[0][5].chessType = "Bishop";
    game.board[0][5].ifHavePiece = true;
    game.board[0][5].index = 1;

    //set black Queen
    //newQueen = new Queen;
    row = QString::number(0);
    col = QString::number(3);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconBQueen);
    newQueen->x = 3;
    newQueen->y = 0;
    game.Black.queens.push_back(*newQueen);
    game.board[0][3].player = 'b';
    game.board[0][3].chessType = "Queen";
    game.board[0][3].ifHavePiece = true;
    game.board[0][3].index = 0;

    //set black King
    row = QString::number(0);
    col = QString::number(4);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconBKing);
    game.Black.king.x = 4;
    game.Black.king.x = 0;
    game.board[0][4].player = 'b';
    game.board[0][4].chessType = "King";
    game.board[0][4].ifHavePiece = true;
    game.board[0][4].index = 0;

    //set white Rook
    //newRook = new Rook;
    row = QString::number(7);
    col = QString::number(0);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconWRook);
    newRook->x = 0;
    newRook->y = 7;
    game.White.rooks.push_back(*newRook);
    game.board[7][0].player = 'w';
    game.board[7][0].chessType = "Rook";
    game.board[7][0].ifHavePiece = true;
    game.board[7][0].index = 0;
    //newRook = new Rook;
    row = QString::number(7);
    col = QString::number(7);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconWRook);
    newRook->x = 7;
    newRook->y = 7;
    game.White.rooks.push_back(*newRook);
    game.board[7][7].player = 'w';
    game.board[7][7].chessType = "Rook";
    game.board[7][7].ifHavePiece = true;
    game.board[7][7].index = 1;

    //set white Knight
    //newKnight = new Knight;
    row = QString::number(7);
    col = QString::number(1);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconWKnight);
    newKnight->x = 1;
    newKnight->y = 7;
    game.White.knights.push_back(*newKnight);
    game.board[7][1].player = 'w';
    game.board[7][1].chessType = "Knight";
    game.board[7][1].ifHavePiece = true;
    game.board[7][1].index = 0;
    //newKnight = new Knight;
    row = QString::number(7);
    col = QString::number(6);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconWKnight);
    newKnight->x = 6;
    newKnight->y = 7;
    game.White.knights.push_back(*newKnight);
    game.board[7][6].player = 'w';
    game.board[7][6].chessType = "Knight";
    game.board[7][6].ifHavePiece = true;
    game.board[7][6].index = 1;

    //set white Bishop
    //newBishop = new Bishop;
    row = QString::number(7);
    col = QString::number(2);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconWBishop);
    newBishop->x = 2;
    newBishop->y = 7;
    game.White.bishops.push_back(*newBishop);
    game.board[7][2].player = 'w';
    game.board[7][2].chessType = "Bishop";
    game.board[7][2].ifHavePiece = true;
    game.board[7][2].index = 0;
    //newBishop = new Bishop;
    row = QString::number(7);
    col = QString::number(5);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconWBishop);
    newBishop->x = 5;
    newBishop->y = 7;
    game.White.bishops.push_back(*newBishop);
    game.board[7][5].player = 'w';
    game.board[7][5].chessType = "Bishop";
    game.board[7][5].ifHavePiece = true;
    game.board[7][5].index = 1;

    //set white Queen
    //newQueen = new Queen;
    row = QString::number(7);
    col = QString::number(3);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconWQueen);
    newQueen->x = 3;
    newQueen->y = 7;
    game.White.queens.push_back(*newQueen);
    game.board[7][3].player = 'w';
    game.board[7][3].chessType = "Queen";
    game.board[7][3].ifHavePiece = true;
    game.board[7][3].index = 0;

    //set white King
    row = QString::number(7);
    col = QString::number(4);
    lab = this->findChild<MyLabel*>(row + " " + col);
    lab->setPixmap(*iconWKing);
    game.White.king.x = 4;
    game.White.king.y = 7;
    game.board[7][4].player = 'w';
    game.board[7][4].chessType = "King";
    game.board[7][4].ifHavePiece = true;
    game.board[7][4].index = 1;

    printInformation();
}

//just to set images
void MainWindow::initIcon()
{
    iconWKing = new QPixmap("./images/WKing.png");
    iconWQueen = new QPixmap("./images/WQueen.png");
    iconWBishop = new QPixmap("./images/WBishop.png");
    iconWKnight = new QPixmap("./images/WKnight.png");
    iconWRook = new QPixmap("./images/WRook.png");
    iconWPawn = new QPixmap("./images/WPawn.png");
    iconBKing = new QPixmap("./images/BKing.png");
    iconBQueen = new QPixmap("./images/BQueen.png");
    iconBBishop = new QPixmap("./images/BBishop.png");
    iconBKnight = new QPixmap("./images/BKnight.png");
    iconBRook = new QPixmap("./images/BRook.png");
    iconBPawn = new QPixmap("./images/BPawn.png");
    *iconWKing = iconWKing->scaled(60,60);
    *iconWQueen = iconWQueen->scaled(60,60);
    *iconWBishop = iconWBishop->scaled(60,60);
    *iconWKnight = iconWKnight->scaled(60,60);
    *iconWRook = iconWRook->scaled(60,60);
    *iconWPawn = iconWPawn->scaled(60,60);
    *iconBKing = iconBKing->scaled(60,60);
    *iconBQueen = iconBQueen->scaled(60,60);
    *iconBBishop = iconBBishop->scaled(60,60);
    *iconBKnight = iconBKnight->scaled(60,60);
    *iconBRook = iconBRook->scaled(60,60);
    *iconBPawn = iconBPawn->scaled(60,60);
}

void MainWindow::printInformation()
{
    system("cls");
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            cout << i<<j;
            if(game.board[i][j].ifHavePiece)
            {
                cout << game.board[i][j].player;
                cout << game.board[i][j].chessType;
            }

            if(game.board[i][j].canMove)
            {
                cout << "c";
            }
            cout << "in"<<game.board[i][j].index;
            //cout << "bt"<<game.board[i][j].bTarget;
            //cout << "wt"<<game.board[i][j].wTarget;
            cout <<" ";
        }

        cout << "\n";
    }
}
