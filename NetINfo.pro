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
	databaseManagement.cpp	\
	bufferPool.cpp \
	jsonFileRead.cpp


HEADERS  += mainwindow.h	\
	   capture.hpp	\
	   databaseManagement.hpp	\
	   bufferPool.hpp \
	   jsonFileRead.hpp

FORMS    += mainwindow.ui

LIBS += -lpcap \
    -lsqlite3 \
    -lboost_serialization   \
    -lboost_thread	\
    -ljson_linux-gcc-4.6_libmt   \
    -lboost_date_time-mt	\
    -lboost_system-mt	\
    -lpthread	\
    -lboost_thread	\
#    -ljson_linux-gcc-4.4.3_libmt
