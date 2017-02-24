#-------------------------------------------------
#
# Project created by QtCreator 2017-02-16T22:27:40
# made by zhang yaxin
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dac
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
    login.cpp \
    mainwindow.cpp \
    usercreate.cpp \
    objcreate.cpp \
    blackcardset.cpp \
    blackcardrevoke.cpp \
    authorize.cpp \
    withdraw.cpp \
    objdelete.cpp \
    readpower.cpp \
    writepower.cpp

HEADERS  += login.h \
    mainwindow.h \
    usercreate.h \
    database.h \
    objcreate.h \
    blackcardset.h \
    blackcardrevoke.h \
    authorize.h \
    withdraw.h \
    objdelete.h \
    readpower.h \
    writepower.h

FORMS    += login.ui \
    mainwindow.ui \
    usercreate.ui \
    objcreate.ui \
    blackcardset.ui \
    blackcardrevoke.ui \
    authorize.ui \
    withdraw.ui \
    objdelete.ui \
    readpower.ui \
    writepower.ui


