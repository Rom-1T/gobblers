TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        board.cpp \
        cell.cpp \
        main.cpp \
        piece.cpp

HEADERS += \
    board.h \
    cell.h \
    config.h \
    piece.h \
    playerEnum.h \
    statusEnum.h
