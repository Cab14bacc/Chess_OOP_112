QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bishop.cpp \
    GameManager.cpp \
    King.cpp \
    Knight.cpp \
    Pawn.cpp \
    Player.cpp \
    Queen.cpp \
    Rook.cpp \
    main.cpp \
    mainwindow.cpp \
    viewmanager.cpp

HEADERS += \
    Bishop.h \
    GameManager.h \
    King.h \
    Knight.h \
    Pawn.h \
    Player.h \
    Queen.h \
    Rook.h \
    mainwindow.h \
    myLabel.h \
    viewmanager.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
