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
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(850, 667);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 20, 571, 521));
        gameBoard = new QGridLayout(gridLayoutWidget);
        gameBoard->setObjectName(QString::fromUtf8("gameBoard"));
        gameBoard->setContentsMargins(0, 0, 0, 0);
        newGame = new QPushButton(centralwidget);
        newGame->setObjectName(QString::fromUtf8("newGame"));
        newGame->setGeometry(QRect(640, 90, 171, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(12);
        newGame->setFont(font);
        undo = new QPushButton(centralwidget);
        undo->setObjectName(QString::fromUtf8("undo"));
        undo->setGeometry(QRect(640, 160, 171, 51));
        QFont font1;
        font1.setPointSize(12);
        undo->setFont(font1);
        redo = new QPushButton(centralwidget);
        redo->setObjectName(QString::fromUtf8("redo"));
        redo->setGeometry(QRect(640, 230, 171, 51));
        redo->setFont(font1);
        blackTime = new QLabel(centralwidget);
        blackTime->setObjectName(QString::fromUtf8("blackTime"));
        blackTime->setGeometry(QRect(640, 10, 181, 51));
        QFont font2;
        font2.setPointSize(16);
        blackTime->setFont(font2);
        whiteTime = new QLabel(centralwidget);
        whiteTime->setObjectName(QString::fromUtf8("whiteTime"));
        whiteTime->setGeometry(QRect(640, 470, 191, 51));
        whiteTime->setFont(font2);
        Resign = new QPushButton(centralwidget);
        Resign->setObjectName(QString::fromUtf8("Resign"));
        Resign->setGeometry(QRect(640, 300, 171, 51));
        QFont font3;
        font3.setPointSize(14);
        Resign->setFont(font3);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 490, 31, 51));
        label->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 420, 31, 51));
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 350, 31, 51));
        label_3->setFont(font1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 290, 31, 51));
        label_4->setFont(font1);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 220, 31, 51));
        label_5->setFont(font1);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 160, 31, 51));
        label_6->setFont(font1);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 90, 31, 51));
        label_7->setFont(font1);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 30, 31, 51));
        label_8->setFont(font1);
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(70, 530, 31, 51));
        label_9->setFont(font3);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(140, 530, 31, 51));
        label_10->setFont(font3);
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(210, 530, 31, 51));
        label_11->setFont(font3);
        label_12 = new QLabel(centralwidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(280, 530, 31, 51));
        label_12->setFont(font3);
        label_13 = new QLabel(centralwidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(350, 530, 31, 51));
        label_13->setFont(font3);
        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(430, 530, 31, 51));
        label_14->setFont(font3);
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(490, 530, 31, 51));
        label_15->setFont(font3);
        label_16 = new QLabel(centralwidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(560, 530, 31, 51));
        label_16->setFont(font3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 850, 26));
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
        label->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "a", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "b", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "c", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "d", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "e", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "f", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "g", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "h", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
