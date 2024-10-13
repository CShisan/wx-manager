QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp sources/wxm.cpp \
    sources/carrier/carrier.cpp \
    sources/nav/nav.cpp \
    sources/nav/nav_center.cpp \
    sources/nav/nav_header.cpp \
    sources/nav/nav_selector.cpp \
    sources/nav/nav_tag.cpp

HEADERS += sources/wxm.h \
    sources/carrier/carrier.h \
    sources/nav/nav.h \
    sources/nav/nav_center.h \
    sources/nav/nav_header.h \
    sources/nav/nav_selector.h \
    sources/nav/nav_tag.h

FORMS += sources/wxm.ui \
    sources/carrier/carrier.ui \
    sources/nav/nav.ui \
    sources/nav/nav_center.ui \
    sources/nav/nav_header.ui \
    sources/nav/nav_selector.ui \
    sources/nav/nav_tag.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
