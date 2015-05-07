#-------------------------------------------------
#
# Project created by QtCreator 2015-04-12T14:15:21
#
#-------------------------------------------------

QT       += core gui
QT       += xml   #support operate xml files
QMAKE_LFLAGS += /INCREMENTAL:NO
qtHaveModule(printsupport): QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BING_TOOL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my_label.cpp

HEADERS  += mainwindow.h \
    crop_rect.h \
    my_label.h

FORMS    += mainwindow.ui
