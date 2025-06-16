QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp sources/views/wxm.cpp \
    sources/common/utils/wechat.cpp \
    sources/config/property.cpp \
    sources/views/carrier/carrier.cpp \
    sources/views/carrier/carrier_slot.cpp \
    sources/views/nav/nav.cpp \
    sources/views/nav/nav_center.cpp \
    sources/views/nav/nav_header.cpp \
    sources/views/nav/nav_selector.cpp \
    sources/views/nav/nav_tag.cpp \
    sources/views/settings/settings.cpp

HEADERS += sources/views/wxm.h \
    sources/common/utils/wechat.h \
    sources/config/property.h \
    sources/views/carrier/carrier.h \
    sources/views/carrier/carrier_slot.h \
    sources/views/nav/nav.h \
    sources/views/nav/nav_center.h \
    sources/views/nav/nav_header.h \
    sources/views/nav/nav_selector.h \
    sources/views/nav/nav_tag.h \
    sources/views/settings/settings.h

FORMS += sources/views/wxm.ui \
    sources/views/carrier/carrier.ui \
    sources/views/nav/nav.ui \
    sources/views/nav/nav_center.ui \
    sources/views/nav/nav_header.ui \
    sources/views/nav/nav_selector.ui \
    sources/views/nav/nav_tag.ui \
    sources/views/settings/settings.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources.qrc

RC_ICONS = bubbles.ico

# copy_files.files = $$PWD/starter
# copy_files.path = $$OUT_PWD
# COPIES += copy_files
