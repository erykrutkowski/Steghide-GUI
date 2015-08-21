#-------------------------------------------------
#
# Project created by QtCreator 2015-08-17T15:07:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Steghide-GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    FilesToAddListModel.cpp \
    FilesToAdd.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    FilesToAddListModel.h \
    FilesToAdd.h

FORMS    += mainwindow.ui \
    dialog.ui

DISTFILES +=

RESOURCES += \
    imageresources.qrc
