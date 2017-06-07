#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T13:27:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = btube_gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dateneingabe.cpp \
    fluid.cpp \
    rohr.cpp \
    qcustomplot.cpp \
    plotter.cpp \
    stroemung.cpp \
    cli.cpp

HEADERS  += mainwindow.h \
    dateneingabe.h \
    fluid.h \
    rohr.h \
    stroemung.h \
    tests/test.h \
    tests/testDefinitionen.h \
    qcustomplot.h \
    plotter.h \
    cli.h

FORMS    += dateneingabe.ui \
    mainwindow.ui \
    plotter.ui
