#-------------------------------------------------
#
# Project created by QtCreator 2024-12-03T12:22:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EETIS_TestApplication
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    modbuscomm.cpp \
    bdobus.cpp \
    bbat.cpp \
    bfcmdf.cpp \
    rfu.cpp \
    dispopup.cpp \
    stdp.cpp

HEADERS += \
        mainwindow.h \
    modbuscomm.h \
    bdobus.h \
    bbat.h \
    bfcmdf.h \
    rfu.h \
    dispopup.h \
    stdp.h

FORMS += \
        mainwindow.ui \
    bdobus.ui \
    bbat.ui \
    bfcmdf.ui \
    rfu.ui \
    dispopup.ui \
    stdp.ui

RESOURCES += \
    images.qrc
