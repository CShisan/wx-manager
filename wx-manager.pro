QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    carrier.cpp \
    carrier_slot.cpp \
    main.cpp \
    navmain.cpp \
    setting.cpp \
    wxmanager.cpp \
    global.cpp \
    selector.cpp \
    wechat.cpp \
    wxmmenubar.cpp

HEADERS += \
    carrier.h \
    carrier_slot.h \
    navmain.h \
    setting.h \
    wxmanager.h \
    global.h \
    selector.h \
    wechat.h \
    wxmmenubar.h


FORMS += \
    wxmanager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

# 指定包含路径
# INCLUDEPATH += $$PWD/starter
