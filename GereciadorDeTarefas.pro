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
    supply.cpp \
    process.cpp \
    tojson.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    memory.h \
    cpu.h \
    supply.h \
    process.h \
    tojson.h

FORMS    += mainwindow.ui
