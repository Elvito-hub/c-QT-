#-------------------------------------------------
#
# Project created by QtCreator 2021-08-23T14:41:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dailyPlanner
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    clockwidget.cpp \
    addactivity.cpp \
    mydb.cpp \
    today_acts.cpp \
    calendar_acts.cpp \
    piechart.cpp \
    polarchart.cpp \
    progressfallwidget.cpp \
    linechart.cpp \
    delegate.cpp \
    roadmaps.cpp \
    addroadmap.cpp \
    mydbrm.cpp \
    roadmapdraw.cpp

HEADERS += \
        mainwindow.h \
    clockwidget.h \
    addactivity.h \
    mydb.h \
    today_acts.h \
    calendar_acts.h \
    piechart.h \
    polarchart.h \
    progressfallwidget.h \
    linechart.h \
    delegate.h \
    roadmaps.h \
    addroadmap.h \
    mydbrm.h \
    roadmapdraw.h

FORMS += \
        mainwindow.ui \
    addactivity.ui \
    today_acts.ui \
    calendar_acts.ui \
    piechart.ui \
    polarchart.ui \
    progressfallwidget.ui \
    linechart.ui \
    roadmaps.ui \
    addroadmap.ui \
    roadmapdraw.ui

RESOURCES += \
    resc.qrc
