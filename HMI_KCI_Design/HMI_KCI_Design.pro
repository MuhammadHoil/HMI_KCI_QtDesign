#-------------------------------------------------
#
# Project created by QtCreator 2025-02-14T11:18:55
#
#-------------------------------------------------

QT       += core gui sql network multimedia multimediawidgets webenginewidgets serialbus serialbus serialport positioning

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HMI_KCI_Design
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    connectionstatus.cpp \
    pecustatus.cpp \
    displaymenu.cpp \
    announcermenu.cpp \
    cctvview.cpp \
    windowmanager.cpp \
    ioreader.cpp

HEADERS += \
        mainwindow.h \
    connectionstatus.h \
    pecustatus.h \
    displaymenu.h \
    announcermenu.h \
    cctvview.h \
    windowmanager.h \
    ioreader.h

FORMS += \
        mainwindow.ui \
    connectionstatus.ui \
    pecustatus.ui \
    displaymenu.ui \
    announcermenu.ui \
    cctvview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    material_qt_design/material_qt_design.qrc

# Tambahkan path ke VLC-Qt
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lVLCQtCore -lVLCQtWidgets -lVLCQtQml

CONFIG += link_pkgconfig
PKGCONFIG += libVLCQtCore libVLCQtWidgets

DISTFILES += \
    ../config/Respati/pids-hmi.conf

