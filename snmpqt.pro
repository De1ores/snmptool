QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h \
    windows/include/snmp_pp.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
win32 {
    INCLUDEPATH += $$PWD/windows/include
    CONFIG(debug, debug|release) {
        LIBS +=      -L$$PWD/windows/lib/ -llibdesd \
                     -L$$PWD/windows/lib/ -lSNMP++d \
                     -L$$PWD/windows/lib/ -lWS2_32
    } else {
        LIBS +=      -L$$PWD/windows/lib/ -llibdes \
                     -L$$PWD/windows/lib/ -lSNMP++ \
                     -L$$PWD/windows/lib/ -lWS2_32
    }
}
