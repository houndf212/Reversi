#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T10:44:13
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = QtReversi
TEMPLATE = app


SOURCES += main.cpp\
        qreversi.cpp \
    game.cc \
    board.cc \
    virtualplayer.cc \
    boardguiviewer.cpp \
    threadgame.cpp \
    humanguiplayer.cpp \
    virtualguiplayer.cpp \
    reversimainwindow.cpp \
    newgamedialog.cpp

HEADERS  += qreversi.h \
    player.h \
    game.h \
    boardviewer.h \
    board.h \
    virtualplayer.h \
    boardguiviewer.h \
    threadgame.h \
    humanguiplayer.h \
    virtualguiplayer.h \
    guiplayer.h \
    reversimainwindow.h \
    newgamedialog.h

RESOURCES += \
    Icon.qrc

FORMS += \
    newgamedialog.ui
