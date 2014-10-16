#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T02:46:34
#
#-------------------------------------------------

QT       += core gui

TARGET = NetINfo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp	\
        capture.cpp \


HEADERS  += mainwindow.h	\
	   capture.hpp

FORMS    += mainwindow.ui

LIBS += -lpcap \
    -lsqlite3 \
    -lboost_serialization   \
    -lboost_thread
