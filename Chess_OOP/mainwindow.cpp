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
#include <QDialog>

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
    setSound();
    startSound->play();//plat BGM
    startSound->setLoops(-1);//repeat play
    connect(&whiteTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    connect(&blackTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Intent: set label and put color on it
// Pre: no input
// Post: set label and put color on it
void MainWindow::setBoard()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            //creat label
            label = new MyLabel(this);
            label->setParent(this);
            label->setFixedSize(60,60);
            label->setText("");

            //put color
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

// Intent: if label clicled, call this function
// Pre: need press new game first
// Post: select chess or move chess
void MainWindow::labelClicked()
{
    clickSound->play();

    if(game.playerTurn == '0')
        return;

    //get row and col
    MyLabel *lab = qobject_cast<MyLabel*>(sender());
    QString Name = lab->objectName();
    string words[2];
    split(words,Name);
    int curRow = stoi(words[0]);
    int curCol = stoi(words[1]);

    //select chess
    if(game.clickTimes == 1)
    {
        game.showCanMove(curRow, curCol);
        update();
        printInformation();
    }
    //move chess
    else
    {
        game.playerMove(curRow, curCol);
        update();

        //if kill self
        if(game.board[game.White.king.y][game.White.king.x].bTarget >= 1 && game.playerTurn == 'b')
        {
            on_undo_clicked();
            game.steps.resize(game.curStep + 1);
            game.fens.resize(game.curStep + 1);
        }
        else if(game.board[game.Black.king.y][game.Black.king.x].wTarget >= 1 && game.playerTurn == 'w')
        {
            game.steps.resize(game.curStep + 1);
            game.fens.resize(game.curStep + 1);
            on_undo_clicked();
        }

        //if game over
        if(game.judgeWinOrLose() == blackWin)
        {
            showResultWindow(blackWin);
        }
        else if(game.judgeWinOrLose() == whiteWin)
        {
            showResultWindow(whiteWin);
        }
        else if(game.ifDraw || game.noEat == 100 || (game.playerTurn == 'w' && !game.ifWhiteCanMove) || (game.playerTurn == 'b' && !game.ifBlackCanMove))
        {
            showResultWindow(draw);
        }

        game.clickTimes = 1;
        printInformation();
    }
}

// Intent: update ui
// Pre: on input
// Post: update ui
void MainWindow::update()
{
    //Promoting
    for(int i = 0; i < 8; i++)
    {
        if(game.board[0][i].chessType == "Pawn")
        {
            if(game.White.pawns[game.board[0][i].index].ifPromoting == false)
                Promoting(0, i);
            else
                game.Promoting(0, i, game.White.pawns[game.board[0][i].index].promotingType);
        }
        else if(game.board[7][i].chessType == "Pawn")
        {
            if(game.Black.pawns[game.board[7][i].index].ifPromoting == false)
                Promoting(7, i);
            else
                game.Promoting(7, i, game.Black.pawns[game.board[7][i].index].promotingType);
        }
    }

    //update board
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            MyLabel *lab;
            QString row = QString::number(i);
            QString col = QString::number(j);
            lab = this->findChild<MyLabel*>(row + " " + col);

            //fill color
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

            //check
            if(game.board[i][j].ifHavePiece && game.board[i][j].chessType == "King")
            {
                if(game.board[i][j].player == 'w' && game.board[i][j].bTarget >= 1)
                    lab->setStyleSheet("QLabel{background-color:rgb(237,28,36);}");
                else if(game.board[i][j].player == 'b' && game.board[i][j].wTarget >= 1)
                    lab->setStyleSheet("QLabel{background-color:rgb(237,28,36);}");
            }

            //set icon
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
                //remove chess icon
                lab->clear();
            }
        }
    }

    //update move
    //new game
    if(game.moves[game.curStep].chessPlayer == '0')
        ui->displayMove->setText("");
    else
    {
        QString originalRow, originalCol, afterRow, afterCol;

        //set originalRow
        switch(game.moves[game.curStep].originalPos[0])
        {
        case 0:
            originalRow = "8";
            break;
        case 1:
            originalRow = "7";
            break;
        case 2:
            originalRow = "6";
            break;
        case 3:
            originalRow = "5";
            break;
        case 4:
            originalRow = "4";
            break;
        case 5:
            originalRow = "3";
            break;
        case 6:
            originalRow = "2";
            break;
        case 7:
            originalRow = "1";
            break;
        }

        //set originalCol
        switch(game.moves[game.curStep].originalPos[1])
        {
        case 0:
            originalCol = "a";
            break;
        case 1:
            originalCol = "b";
            break;
        case 2:
            originalCol = "c";
            break;
        case 3:
            originalCol = "d";
            break;
        case 4:
            originalCol = "e";
            break;
        case 5:
            originalCol = "f";
            break;
        case 6:
            originalCol = "g";
            break;
        case 7:
            originalCol = "h";
            break;
        }

        //set afterRow
        switch(game.moves[game.curStep].afterPos[0])
        {
        case 0:
            afterRow = "8";
            break;
        case 1:
            afterRow = "7";
            break;
        case 2:
            afterRow = "6";
            break;
        case 3:
            afterRow = "5";
            break;
        case 4:
            afterRow = "4";
            break;
        case 5:
            afterRow = "3";
            break;
        case 6:
            afterRow = "2";
            break;
        case 7:
            afterRow = "1";
            break;
        }

        //set afterCol
        switch(game.moves[game.curStep].afterPos[1])
        {
        case 0:
            afterCol = "a";
            break;
        case 1:
            afterCol = "b";
            break;
        case 2:
            afterCol = "c";
            break;
        case 3:
            afterCol = "d";
            break;
        case 4:
            afterCol = "e";
            break;
        case 5:
            afterCol = "f";
            break;
        case 6:
            afterCol = "g";
            break;
        case 7:
            afterCol = "h";
            break;
        }

        if(game.moves[game.curStep].chessPlayer == 'w')
        {
            if(game.moves[game.curStep].chessType == "Pawn")
            {
                ui->displayMove->setText("White Pawn " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "Rook")
            {
                ui->displayMove->setText("White Rook " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "Knight")
            {
                ui->displayMove->setText("White Knight " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "Bishop")
            {
                ui->displayMove->setText("White Bishop " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "Queen")
            {
                ui->displayMove->setText("White Queen " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "King")
            {
                ui->displayMove->setText("White King " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
        }
        else//game.moves[game.curStep].chessPlayer == 'b'
        {
            if(game.moves[game.curStep].chessType == "Pawn")
            {
                ui->displayMove->setText("Black Pawn " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "Rook")
            {
                ui->displayMove->setText("Black Rook " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "Knight")
            {
                ui->displayMove->setText("Black Knight " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "Bishop")
            {
                ui->displayMove->setText("Black Bishop " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "Queen")
            {
                ui->displayMove->setText("Black Queen " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
            else if(game.moves[game.curStep].chessType == "King")
            {
                ui->displayMove->setText("Black King " + originalCol + originalRow + " to " + afterCol + afterRow);
            }
        }
    }
}

// Intent: get row and col
// Pre: input string array, Qstring
// Post: split Qstring
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

// Intent: set new game
// Pre: no input
// Post: set new game
void MainWindow::on_newGame_clicked()
{
    clickSound->play();
    whiteTimer.stop();
    blackTimer.stop();
    //chose who first
    shoeWhoFirst();
    //reset game
    resetGame();

    //reset all information
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

    QString row;
    QString col;
    MyLabel *lab;
    Queen *newQueen = new Queen;
    Bishop *newBishop = new Bishop;
    Knight *newKnight = new Knight;
    Rook *newRook = new Rook;
    newRook->ifMove = false;
    Pawn *newPawn = new Pawn;

    //set pawn
    for(int i = 0; i < 8; i++)
    {
        newPawn = new Pawn;
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
        newPawn = new Pawn;
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
    game.Black.king.ifMove = false;
    game.Black.king.x = 4;
    game.Black.king.y = 0;
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
    game.White.king.ifMove = false;
    game.board[7][4].player = 'w';
    game.board[7][4].chessType = "King";
    game.board[7][4].ifHavePiece = true;
    game.board[7][4].index = 1;

    game.computeTarget();
    game.recordCurBoard();
    game.steps.push_back(game.curBoard);
    game.transBoardToFen();
    game.fens.push_back(game.fen);
    game.moves.push_back(game.curMove);
    update();
    printInformation();
}

// Intent: set images
// Pre: no input
// Post: set images
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

// Intent: print information to debug
// Pre: no input
// Post: print information
void MainWindow::printInformation()
{
    //system("cls");
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
                //cout << "c";
            }
            //cout << "in"<<game.board[i][j].index;
            cout << "bt"<<game.board[i][j].bTarget;
            cout << "wt"<<game.board[i][j].wTarget;
            cout <<" ";
        }

        cout << "\n";
    }

    cout << game.curStep<<" "<<game.steps.size()<<endl;
    cout << game.fen<<endl;
    cout << game.wPawn <<game.wRook<<game.wKnight<<game.wBishop<<game.wQueen<<endl;
    cout << game.bPawn <<game.bRook<<game.bKnight<<game.bBishop<<game.bQueen<<endl;
    //cout << "noEat:" << game.noEat<<endl;

    if(game.ifWhiteCanMove)
    {
        cout << "ifWhiteCanMove: true";
    }
    else
    {
        cout << "ifWhiteCanMove: false";
    }
    cout << endl;
    if(game.ifBlackCanMove)
    {
        cout << "ifBlackCanMove: true";
    }
    else
    {
        cout << "ifBlackCanMove: false";
    }
    cout << endl;
    if(game.ifDraw)
    {
        cout <<"ifDraw: true";
    }
    else
    {
        cout << "ifDraw: false";
    }
    cout << endl;
    if(game.White.king.ifMove)
    {
        cout << "White.king.ifMove = true";
    }
    else
    {
        cout << "White.king.ifMove = false";
    }
    cout << endl;
    if(game.Black.king.ifMove)
    {
        cout << "Black.king.ifMove = true";
    }
    else
    {
        cout << "Black.king.ifMove = false";
    }
    cout << endl;
    if(game.steps[game.curStep].ifWhiteKingMove)
    {
        cout << "White.king.ifMove: true";
    }
    else
    {
        cout << "White.king.ifMove: false";
    }
    cout << endl;
    if(game.steps[game.curStep].ifBlackKingMove)
    {
        cout << "Black.king.ifMove: true";
    }
    else
    {
        cout << "Black.king.ifMove: false";
    }
    cout << endl;
}

// Intent: undo
// Pre: no input
// Post: undo
void MainWindow::on_undo_clicked()
{
    clickSound->play();

    if(game.curStep != 0)
    {
        //move to previous
        game.curStep--;
        loadBoard();
        update();
        printInformation();
        game.judgeIfPlayerCanMove(game.playerTurn);
    }
}

// Intent: redo
// Pre: no input
// Post: redo
void MainWindow::on_redo_clicked()
{
    clickSound->play();

    //game not start
    if(game.playerTurn == '0')
        return;

    //move to after
    if(game.curStep != game.steps.size() - 1)
    {
        game.curStep++;
        loadBoard();
        update();
        printInformation();
        game.judgeIfPlayerCanMove(game.playerTurn);
    }
}

// Intent: load board form steps
// Pre: no input
// Post: load board form steps
void MainWindow::loadBoard()
{
    //load all information
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            game.board[i][j].wTarget = game.steps[game.curStep].curBoard[i][j].wTarget;
            game.board[i][j].bTarget = game.steps[game.curStep].curBoard[i][j].bTarget;
            game.board[i][j].player = game.steps[game.curStep].curBoard[i][j].player;
            game.board[i][j].chessType = game.steps[game.curStep].curBoard[i][j].chessType;
            game.board[i][j].index = game.steps[game.curStep].curBoard[i][j].index;
            game.board[i][j].canMove = game.steps[game.curStep].curBoard[i][j].canMove;
            game.playerTurn = game.steps[game.curStep].playerTurn;
            game.board[i][j].ifHavePiece = game.steps[game.curStep].curBoard[i][j].ifHavePiece;

            //laod special information
            if(game.board[i][j].ifHavePiece)
            {
                if(game.board[i][j].player == 'w')
                {
                    if(game.board[i][j].chessType == "Pawn")
                    {
                        game.White.pawns[game.board[i][j].index].y = i;
                        game.White.pawns[game.board[i][j].index].x = j;
                        game.White.pawns[game.board[i][j].index].ifmove2Step = game.steps[game.curStep].curBoard[i][j].ifPawnMove2Step;
                        game.White.pawns[game.board[i][j].index].inNextTurn = game.steps[game.curStep].curBoard[i][j].inPawnNextTurn;
                    }
                    else if(game.board[i][j].chessType == "Rook")
                    {
                        game.White.rooks[game.board[i][j].index].y = i;
                        game.White.rooks[game.board[i][j].index].x = j;
                        game.White.rooks[game.board[i][j].index].ifMove = game.steps[game.curStep].curBoard[i][j].ifRookMove;
                    }
                    else if(game.board[i][j].chessType == "Knight")
                    {
                        game.White.knights[game.board[i][j].index].y = i;
                        game.White.knights[game.board[i][j].index].x = j;
                    }
                    else if(game.board[i][j].chessType == "Bishop")
                    {
                        game.White.bishops[game.board[i][j].index].y = i;
                        game.White.bishops[game.board[i][j].index].x = j;
                    }
                    else if(game.board[i][j].chessType == "Queen")
                    {
                        game.White.queens[game.board[i][j].index].y = i;
                        game.White.queens[game.board[i][j].index].x = j;
                    }
                    else if(game.board[i][j].chessType == "King")
                    {
                        game.White.king.y = i;
                        game.White.king.x = j;
                        game.White.king.ifMove = game.steps[game.curStep].ifWhiteKingMove;
                    }
                }
                else//game.board[i][j].player == 'b'
                {
                    if(game.board[i][j].chessType == "Pawn")
                    {
                        game.Black.pawns[game.board[i][j].index].y = i;
                        game.Black.pawns[game.board[i][j].index].x = j;
                        game.Black.pawns[game.board[i][j].index].ifmove2Step = game.steps[game.curStep].curBoard[i][j].ifPawnMove2Step;
                        game.Black.pawns[game.board[i][j].index].inNextTurn = game.steps[game.curStep].curBoard[i][j].inPawnNextTurn;
                    }
                    else if(game.board[i][j].chessType == "Rook")
                    {
                        game.Black.rooks[game.board[i][j].index].y = i;
                        game.Black.rooks[game.board[i][j].index].x = j;
                        game.Black.rooks[game.board[i][j].index].ifMove = game.steps[game.curStep].curBoard[i][j].ifRookMove;
                    }
                    else if(game.board[i][j].chessType == "Knight")
                    {
                        game.Black.knights[game.board[i][j].index].y = i;
                        game.Black.knights[game.board[i][j].index].x = j;
                    }
                    else if(game.board[i][j].chessType == "Bishop")
                    {
                        game.Black.bishops[game.board[i][j].index].y = i;
                        game.Black.bishops[game.board[i][j].index].x = j;
                    }
                    else if(game.board[i][j].chessType == "Queen")
                    {
                        game.Black.queens[game.board[i][j].index].y = i;
                        game.Black.queens[game.board[i][j].index].x = j;
                    }
                    else if(game.board[i][j].chessType == "King")
                    {
                        game.Black.king.y = i;
                        game.Black.king.x = j;
                        game.Black.king.ifMove = game.steps[game.curStep].ifBlackKingMove;
                    }
                }
            }
        }
    }
}

// Intent: set time
// Pre: no input
// Post: set time
void MainWindow::setTime()
{
    //set 1 second
    whiteTimer.start(1000);
    blackTimer.start(1000);
    whiteCounter = 10 * 60;
    blackCounter = 10 * 60;
    ui->whiteTime->setAlignment(Qt::AlignCenter);
    ui->blackTime->setAlignment(Qt::AlignCenter);
    ui->whiteTime->setText(QString("%1:%2").arg(whiteCounter / 60, 2, 10, QChar('0')).arg(whiteCounter % 60, 2, 10, QChar('0')));
    ui->blackTime->setText(QString("%1:%2").arg(blackCounter / 60, 2, 10, QChar('0')).arg(blackCounter % 60, 2, 10, QChar('0')));
}

// Intent: update time
// Pre: no input
// Post: update time
void MainWindow::updateTimer()
{
    if(game.playerTurn == 'w')
    {
        whiteTimer.start();
        blackTimer.stop();
        whiteCounter = whiteCounter - 1;
        ui->whiteTime->setText(QString("%1:%2").arg(whiteCounter / 60, 2, 10, QChar('0')).arg(whiteCounter % 60, 2, 10, QChar('0')));
    }
    else if(game.playerTurn == 'b')
    {
        whiteTimer.stop();
        blackTimer.start();
        blackCounter = blackCounter - 1;
        ui->blackTime->setText(QString("%1:%2").arg(blackCounter / 60, 2, 10, QChar('0')).arg(blackCounter % 60, 2, 10, QChar('0')));
    }

    //if time up
    if(whiteCounter == 0)
    {
        whiteTimer.stop();
        //set white lose
        showResultWindow(blackWin);
    }
    else if(blackCounter == 0)
    {
        blackTimer.stop();
        //set black lose
        showResultWindow(whiteWin);
    }
}

// Intent: set sound
// Pre: no input
// Post: set sound
void MainWindow::setSound()
{
    startSound = new QSound("./sounds/RoadtoDazir.wav",this);
    clickSound = new QSound("./sounds/OpenCell.wav",this);
}

// Intent: show result
// Pre: game over
// Post: show result
void MainWindow::showResultWindow(int whoWin)
{
    QDialog *dialog = new QDialog(this);
    QLabel *label = new QLabel(dialog);
    //dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowCloseButtonHint);

    if (whoWin == whiteWin)
    {
        label->setText("White Win!");
    }
    else if(whoWin == blackWin)
    {
        label->setText("Black Win!");
    }
    else//whoWin == draw
    {
        label->setText("Draw!");
    }

    QFont ft;
    ft.setPointSize(16);
    label->setFont(ft);
    label->setAlignment(Qt::AlignCenter);
    dialog->setWindowTitle("Game Result");
    dialog->setFixedSize(200, 150);
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(label);

    //set replay
    QPushButton *replayBtn = new QPushButton("Replay", dialog);
    connect(replayBtn, &QPushButton::clicked, [=](){
        dialog->close();//close window
        //function to execute
        clickSound->play();
        on_newGame_clicked();
    });

    layout->addWidget(replayBtn);

    //set quit
    QPushButton *quitBtn = new QPushButton("Quit", dialog);
    connect(quitBtn, &QPushButton::clicked, [=](){
        dialog->close();//close window
        //function to execute
        clickSound->play();
        qApp->quit();
    });
    layout->addWidget(quitBtn);

    dialog->setLayout(layout);
    dialog->exec();//display
}

// Intent: reset game
// Pre: new game clicked
// Post: reset game
void MainWindow::resetGame()
{
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
    game.curStep = 0;
    game.steps.clear();
    game.wPawn = 8;
    game.wRook = 2;
    game.wKnight = 2;
    game.wBishop = 2;
    game.wQueen = 1;
    game.bPawn = 8;
    game.bRook = 2;
    game.bKnight = 2;
    game.bBishop = 2;
    game.bQueen = 1;
    game.noEat = 0;
    game.fen = "";
    game.ifWhiteCanMove = true;
    game.ifBlackCanMove = true;
    game.ifDraw = false;
    game.fens.clear();
    setTime();
}

// Intent: Promoting
// Pre: pwan walk to last line
// Post: Promoting
void MainWindow::Promoting(int row, int col)
{
    QDialog *dialogPromoting = new QDialog(this);
    dialogPromoting->setWindowTitle("Promoting");
    QHBoxLayout *layoutPromoting = new QHBoxLayout(dialogPromoting);
    //set queen
    QPushButton *queenBtn = new QPushButton(dialogPromoting);

    connect(queenBtn, &QPushButton::clicked, [=](){
        dialogPromoting->close();//close window
        //function to execute
        clickSound->play();
        game.Promoting(row, col, "Queen");
    });

    layoutPromoting->addWidget(queenBtn);

    //set bishop
    QPushButton *bishopBtn = new QPushButton(dialogPromoting);
    connect(bishopBtn, &QPushButton::clicked, [=](){
        dialogPromoting->close();//close window
        //function to execute
        clickSound->play();
        game.Promoting(row, col, "Bishop");
    });

    layoutPromoting->addWidget(bishopBtn);

    //set knight
    QPushButton *knightBtn = new QPushButton(dialogPromoting);
    connect(knightBtn, &QPushButton::clicked, [=](){
        dialogPromoting->close();//close window
        //function to execute
        clickSound->play();
        game.Promoting(row, col, "Knight");
    });

    layoutPromoting->addWidget(knightBtn);

    //set rook
    QPushButton *rookBtn = new QPushButton(dialogPromoting);
    connect(rookBtn, &QPushButton::clicked, [=](){
        dialogPromoting->close();//close window
        //function to execute
        clickSound->play();
        game.Promoting(row, col, "Rook");
    });

    layoutPromoting->addWidget(rookBtn);

    //set size
    if(game.board[row][col].player == 'w')
    {
        queenBtn->setIcon(QIcon(*iconWQueen));
        queenBtn->setIconSize(iconWQueen->size());
        queenBtn->setFixedSize(70, 70);
        bishopBtn->setIcon(QIcon(*iconWBishop));
        bishopBtn->setIconSize(iconWBishop->size());
        bishopBtn->setFixedSize(70, 70);
        knightBtn->setIcon(QIcon(*iconWKnight));
        knightBtn->setIconSize(iconWKnight->size());
        knightBtn->setFixedSize(70, 70);
        rookBtn->setIcon(QIcon(*iconWRook));
        rookBtn->setIconSize(iconWRook->size());
        rookBtn->setFixedSize(70, 70);
    }
    else//game.board[row][col].player == 'b'
    {
        queenBtn->setIcon(QIcon(*iconBQueen));
        queenBtn->setIconSize(iconBQueen->size());
        queenBtn->setFixedSize(70, 70);
        bishopBtn->setIcon(QIcon(*iconBBishop));
        bishopBtn->setIconSize(iconBBishop->size());
        bishopBtn->setFixedSize(70, 70);
        knightBtn->setIcon(QIcon(*iconBKnight));
        knightBtn->setIconSize(iconBKnight->size());
        knightBtn->setFixedSize(70, 70);
        rookBtn->setIcon(QIcon(*iconBRook));
        rookBtn->setIconSize(iconBRook->size());
        rookBtn->setFixedSize(70, 70);
    }

    dialogPromoting->setLayout(layoutPromoting);
    dialogPromoting->exec();//display
}

// Intent: resign
// Pre: game start
// Post: resign
void MainWindow::on_Resign_clicked()
{
    clickSound->play();

    if(game.playerTurn == 'w')
    {
        showResultWindow(blackWin);
    }
    else if(game.playerTurn == 'b')
    {
        showResultWindow(whiteWin);
    }
}

// Intent: choose who first
// Pre: game start
// Post: choose who first
void MainWindow::shoeWhoFirst()
{
    QDialog *dialogWhoFirst = new QDialog(this);
    dialogWhoFirst->setWindowTitle("Who First");
    dialogWhoFirst->setFixedSize(300, 100);
    dialogWhoFirst->setWindowFlags(dialogWhoFirst->windowFlags() & ~Qt::WindowCloseButtonHint);
    QVBoxLayout *layout = new QVBoxLayout(dialogWhoFirst);

    QFont ft;
    ft.setPointSize(16);

    //set white first
    QPushButton *whiteFirst = new QPushButton("white first", dialogWhoFirst);
    connect(whiteFirst, &QPushButton::clicked, [=](){
        dialogWhoFirst->close();//close window
        //function to execute
        clickSound->play();
        game.playerTurn = 'w';
    });

    whiteFirst->setFont(ft);
    layout->addWidget(whiteFirst);

    //set black first
    QPushButton *blackFirst = new QPushButton("black first", dialogWhoFirst);
    connect(blackFirst, &QPushButton::clicked, [=](){
        dialogWhoFirst->close();//close window
        //function to execute
        clickSound->play();
        game.playerTurn = 'b';
    });

    blackFirst->setFont(ft);
    layout->addWidget(blackFirst);
    dialogWhoFirst->setLayout(layout);
    dialogWhoFirst->exec();//display
}
