#-------------------------------------------------
#
# Project created by QtCreator 2018-06-29T15:44:18
#
#-------------------------------------------------

QT       += core gui webenginewidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CoolChat
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
    addfriend.cpp \
    loginwindow.cpp \
    registerwindow.cpp \
    chatwindow.cpp \
    applicationwindow.cpp \
    systemwindow.cpp

HEADERS += \
        mainwindow.h \
    addfriend.h \
    loginwindow.h \
    registerwindow.h \
    chatwindow.h \
    applicationwindow.h \
    systemwindow.h \
    Server.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    img.qrc

win32{
    PLATFORM = windows
}

unix{
    PLATFORM = linux
}

NETMODULE_PATH = ../../Netmodule

INCLUDEPATH += \
    $$NETMODULE_PATH/include \
    $$NETMODULE_PATH/include/inc \
    $$NETMODULE_PATH/include/http/inc \
    $$NETMODULE_PATH/include/CxxJDK/efc \
    $$NETMODULE_PATH/include/CxxLog4j \

LIBS += \
    -L $$NETMODULE_PATH/lib/$$PLATFORM \
    -lNetmodule -lMina -lLogger -liconv -ldl -lpthread -lcrypto -lefc64 -leso64

QMAKE_CXXFLAGS += -fpermissive