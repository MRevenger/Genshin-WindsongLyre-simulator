QT       += core gui multimedia svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
    c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    button.cpp \
    main.cpp \
    mainwindow.cpp \
    soundplayer.cpp

HEADERS += \
    button.h \
    mainwindow.h \
    soundplayer.h

RC_ICONS = icon.ico
FORMS += \
    mainwindow.ui

# 添加SFML
INCLUDEPATH += \
    E:/Qt/SFML-Qt/include
LIBS += \
    E:/Qt/SFML-Qt/lib/libsfml-audio.a\
    E:/Qt/SFML-Qt/lib/libsfml-system.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
