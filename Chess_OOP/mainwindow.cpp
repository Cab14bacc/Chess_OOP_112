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
    clickSound->play();
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
        printInformation();
        game.clickTimes = 1;
        update();

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
    }
}

void MainWindow::update()
{
    for(int i = 0; i < 8; i++)
    {
        if(game.board[0][i].chessType == "Pawn")
        {
            Promoting(0, i);
        }
        else if(game.board[7][i].chessType == "Pawn")
        {
            Promoting(7, i);
        }
    }

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
    clickSound->play();
    resetGame();

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
    Queen *newQueen = new Queen;
    Bishop *newBishop = new Bishop;
    Knight *newKnight = new Knight;
    Rook *newRook = new Rook;
    newRook->ifMove = false;
    Pawn *newPawn = new Pawn;

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
                //cout << "c";
            }
            //cout << "in"<<game.board[i][j].index;
            cout << "bt"<<game.board[i][j].bTarget;
            cout << "wt"<<game.board[i][j].wTarget;
            cout <<" ";
        }

        cout << "\n";
    }

    //cout << game.curStep<<" "<<game.steps.size()<<endl;
    cout << game.fen<<endl;
    //cout << game.wPawn <<game.wRook<<game.wKnight<<game.wBishop<<game.wQueen<<endl;
    //cout << game.bPawn <<game.bRook<<game.bKnight<<game.bBishop<<game.bQueen<<endl;
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
}

void MainWindow::on_undo_clicked()
{
    clickSound->play();

    if(game.curStep != 0)
    {
        game.curStep--;
        loadBoard();
        update();
        printInformation();
        game.judgeIfPlayerCanMove(game.playerTurn);
    }
}

void MainWindow::on_redo_clicked()
{
    clickSound->play();

    if(game.curStep != game.steps.size() - 1)
    {
        game.curStep++;
        loadBoard();
        update();
        printInformation();
        game.judgeIfPlayerCanMove(game.playerTurn);
    }
}

void MainWindow::loadBoard()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            game.board[i][j].ifHavePiece = game.steps[game.curStep].curBoard[i][j].ifHavePiece;
            game.board[i][j].wTarget = game.steps[game.curStep].curBoard[i][j].wTarget;
            game.board[i][j].bTarget = game.steps[game.curStep].curBoard[i][j].bTarget;
            game.board[i][j].player = game.steps[game.curStep].curBoard[i][j].player;
            game.board[i][j].chessType = game.steps[game.curStep].curBoard[i][j].chessType;
            game.board[i][j].index = game.steps[game.curStep].curBoard[i][j].index;
            game.board[i][j].canMove = game.steps[game.curStep].curBoard[i][j].canMove;
            game.playerTurn = game.steps[game.curStep].playerTurn;
        }
    }
}

void MainWindow::setTime()
{
    whiteTimer.start(1000);
    blackTimer.start(1000);
    whiteCounter = 10 * 60;
    blackCounter = 10 * 60;
    ui->whiteTime->setAlignment(Qt::AlignCenter);
    ui->blackTime->setAlignment(Qt::AlignCenter);
    ui->whiteTime->setText(QString("%1:%2").arg(whiteCounter / 60, 2, 10, QChar('0')).arg(whiteCounter % 60, 2, 10, QChar('0')));
    ui->blackTime->setText(QString("%1:%2").arg(blackCounter / 60, 2, 10, QChar('0')).arg(blackCounter % 60, 2, 10, QChar('0')));
}

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

void MainWindow::setSound()
{
    startSound = new QSound("./sounds/RoadtoDazir.wav",this);
    clickSound = new QSound("./sounds/OpenCell.wav",this);
}

void MainWindow::showResultWindow(int whoWin)
{
    QDialog *dialog = new QDialog(this);
    QLabel *label = new QLabel(dialog);

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

    QPushButton *replayBtn = new QPushButton("Replay", dialog);
    connect(replayBtn, &QPushButton::clicked, [=](){
        dialog->close();//close window
        //function to execute
        on_newGame_clicked();
    });

    layout->addWidget(replayBtn);

    QPushButton *quitBtn = new QPushButton("Quit", dialog);
    connect(quitBtn, &QPushButton::clicked, [=](){
        dialog->close();//close window
        //function to execute
        qApp->quit();
    });
    layout->addWidget(quitBtn);

    dialog->setLayout(layout);
    dialog->exec();//display
}

void MainWindow::resetGame()
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

void MainWindow::Promoting(int row, int col)
{
    QDialog *dialogPromoting = new QDialog(this);
    dialogPromoting->setWindowTitle("Promoting");
    QHBoxLayout *layoutPromoting = new QHBoxLayout(dialogPromoting);
    QPushButton *queenBtn = new QPushButton(dialogPromoting);

    connect(queenBtn, &QPushButton::clicked, [=](){
        dialogPromoting->close();//close window
        //function to execute
        game.Promoting(row, col, "Queen");
    });

    layoutPromoting->addWidget(queenBtn);

    QPushButton *bishopBtn = new QPushButton(dialogPromoting);
    connect(bishopBtn, &QPushButton::clicked, [=](){
        dialogPromoting->close();//close window
        //function to execute
        game.Promoting(row, col, "Bishop");
    });

    layoutPromoting->addWidget(bishopBtn);

    QPushButton *knightBtn = new QPushButton(dialogPromoting);
    connect(knightBtn, &QPushButton::clicked, [=](){
        dialogPromoting->close();//close window
        //function to execute
        game.Promoting(row, col, "Knight");
    });

    layoutPromoting->addWidget(knightBtn);

    QPushButton *rookBtn = new QPushButton(dialogPromoting);
    connect(rookBtn, &QPushButton::clicked, [=](){
        dialogPromoting->close();//close window
        //function to execute
        game.Promoting(row, col, "Rook");
    });

    layoutPromoting->addWidget(rookBtn);

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
