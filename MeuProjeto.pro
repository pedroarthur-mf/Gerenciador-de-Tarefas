#-------------------------------------------------
#
# Project created by QtCreator 2016-10-31T15:18:25
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MeuProjeto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    memory.cpp \
    cpu.cpp \
    supply.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    memory.h \
    cpu.h \
    supply.h

FORMS    += mainwindow.ui
