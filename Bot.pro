QT += core
QT -= gui

TARGET = Bot
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ProbabilityCalculator.cpp \
    Card.cpp \
    Table.cpp \
    Player.cpp

HEADERS += \
    ProbabilityCalculator.h \
    Card.h \
    Table.h \
    Player.h

