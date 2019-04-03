QT       += core gui
QT += printsupport # add print
QT += widgets

TARGET = Notepad2
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    notepad.cpp \
    systemtray.cpp \
    setting.cpp \
    settingpage.cpp \
    utils.cpp \
    editorplain.cpp \
    ndialog.cpp

HEADERS  += \
    notepad.h \
    systemtray.h \
    setting.h \
    settingpage.h \
    utils.h \
    editorplain.h \
    ndialog.h

FORMS    += widget.ui

RESOURCES += \
    resource.qrc

RC_FILE = logo.rc
