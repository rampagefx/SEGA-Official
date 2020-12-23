#-------------------------------------------------
#
# Project created by QtCreator 2020-10-21T12:08:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bubble2020
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    doubleplayermenu.cpp \
        bomb.cpp \
    gamedisplay.cpp \
    doublegame.cpp \
    helpmenu.cpp \
        main.cpp \
        mainwindow.cpp \
        character.cpp \
    misaka.cpp \
    multigame.cpp \
    multimodelclient.cpp \
    multimodelserver.cpp \
    multiplayermenu.cpp \

    npc.cpp \
    peco.cpp \
        singlegame.cpp \
        bombqueue.cpp \
    pikachu.cpp \
    singleplayermenu.cpp \
    socketclient.cpp \
    socketserver.cpp \
    startgamemenu.cpp

HEADERS += \
    filepath.h \
    gamedisplay.h \
    doubleplayermenu.h \
    doublegame.h \
    filepath.h \
    helpmenu.h \
        mainwindow.h \
        character.h \
    misaka.h \
    multigame.h \
    multimodelclient.h \
    multimodelserver.h \
    multiplayermenu.h \
    npc.h \
    peco.h \
        singlegame.h \
        bomb.h \
        mainwindow.h \
        bombqueue.h \
    pikachu.h \
    singleplayermenu.h \
    socketclient.h \
    socketserver.h \
    startgamemenu.h

FORMS += \
    doubleplayermenu.ui \
    helpmenu.ui \
    mainwindow.ui \
    multigame.ui \
    multimodelclient.ui \
    multimodelserver.ui \
    multiplayermenu.ui \
    singleplayermenu.ui \
    startgamemenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += multimedia

DISTFILES += \
    .DS_Store
