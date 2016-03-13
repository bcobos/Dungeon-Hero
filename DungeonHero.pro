#-------------------------------------------------
#
# Project created by QtCreator 2016-02-08T23:48:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DungeonHero
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hero.cpp \
    titlescreen.cpp \
    gameplayboard.cpp \
    enemy1.cpp \
    gameover.cpp \
    finalvictory.cpp

HEADERS  += mainwindow.h \
    hero.h \
    titlescreen.h \
    gameplayboard.h \
    enemy1.h \
    gameover.h \
    finalvictory.h \
    mainpage.h

FORMS    += mainwindow.ui \
    hero.ui \
    level1.ui \
    titlescreen.ui \
    gameplayboard.ui \
    enemy1.ui \
    gameover.ui \
    finalvictory.ui

RESOURCES += \
    images.qrc
