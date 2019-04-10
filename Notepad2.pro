QT       += core gui
QT += printsupport # add print
QT += widgets

TARGET = Notepad2
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    notepad.cpp \
    setting.cpp \
    settingpage.cpp \
    utils.cpp \
    editorplain.cpp \
    replacedialog.cpp \
    finddialog.cpp \
    generalsettingpage.cpp \
    shortcutsettingpage.cpp \
    aboutdialog.cpp

HEADERS  += \
    notepad.h \
    setting.h \
    settingpage.h \
    utils.h \
    editorplain.h \
    replacedialog.h \
    finddialog.h \
    generalsettingpage.h \
    shortcutsettingpage.h \
    aboutdialog.h

FORMS    += widget.ui

RESOURCES += \
    resource.qrc

RC_FILE = logo.rc
