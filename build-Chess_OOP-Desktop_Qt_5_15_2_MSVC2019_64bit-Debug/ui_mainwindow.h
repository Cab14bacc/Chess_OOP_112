/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gameBoard;
    QPushButton *newGame;
    QPushButton *undo;
    QPushButton *redo;
    QLabel *blackTime;
    QLabel *whiteTime;
    QPushButton *Resign;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(838, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 571, 521));
        gameBoard = new QGridLayout(gridLayoutWidget);
        gameBoard->setObjectName(QString::fromUtf8("gameBoard"));
        gameBoard->setContentsMargins(0, 0, 0, 0);
        newGame = new QPushButton(centralwidget);
        newGame->setObjectName(QString::fromUtf8("newGame"));
        newGame->setGeometry(QRect(610, 100, 171, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(12);
        newGame->setFont(font);
        undo = new QPushButton(centralwidget);
        undo->setObjectName(QString::fromUtf8("undo"));
        undo->setGeometry(QRect(610, 170, 171, 51));
        QFont font1;
        font1.setPointSize(12);
        undo->setFont(font1);
        redo = new QPushButton(centralwidget);
        redo->setObjectName(QString::fromUtf8("redo"));
        redo->setGeometry(QRect(610, 240, 171, 51));
        redo->setFont(font1);
        blackTime = new QLabel(centralwidget);
        blackTime->setObjectName(QString::fromUtf8("blackTime"));
        blackTime->setGeometry(QRect(610, 20, 181, 51));
        QFont font2;
        font2.setPointSize(16);
        blackTime->setFont(font2);
        whiteTime = new QLabel(centralwidget);
        whiteTime->setObjectName(QString::fromUtf8("whiteTime"));
        whiteTime->setGeometry(QRect(600, 480, 191, 51));
        whiteTime->setFont(font2);
        Resign = new QPushButton(centralwidget);
        Resign->setObjectName(QString::fromUtf8("Resign"));
        Resign->setGeometry(QRect(610, 310, 171, 51));
        QFont font3;
        font3.setPointSize(14);
        Resign->setFont(font3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 838, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        newGame->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        undo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        redo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        blackTime->setText(QString());
        whiteTime->setText(QString());
        Resign->setText(QCoreApplication::translate("MainWindow", "Resign", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
