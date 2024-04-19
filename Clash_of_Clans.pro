QT       += core gui

QT
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    cannon.cpp \
    castle.cpp \
    enemy.cpp \
    fence.cpp \
    game.cpp \
    gameover.cpp \
    main.cpp \
    menu.cpp \
    tent.cpp \
    winning.cpp \
    worker.cpp \
    workersclan.cpp

HEADERS += \
    bullet.h \
    cannon.h \
    castle.h \
    enemy.h \
    fence.h \
    game.h \
    gameover.h \
    menu.h \
    tent.h \
    winning.h \
    worker.h \
    workersclan.h

FORMS += \
    gameover.ui \
    menu.ui \
    winning.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    img/background.jpeg \
    img/background.png \
    img/cannon.png \
    img/castle.png \
    img/enemy.png \
    img/fence.png \
    img/gameover.jpg \
    img/grass.png \
    img/icon.png
