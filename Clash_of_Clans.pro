QT       += core gui multimedia

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
    gift.cpp \
    graph.cpp \
    healthbar.cpp \
    main.cpp \
    menu.cpp \
    node.cpp \
    options.cpp \
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
    gift.h \
    graph.h \
    healthbar.h \
    menu.h \
    node.h \
    options.h \
    tent.h \
    winning.h \
    worker.h \
    workersclan.h

FORMS += \
    gameover.ui \
    menu.ui \
    options.ui \
    winning.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    audio/bullet.wav \
    audio/enemydamagefence.wav \
    audio/enemydamagefenceandcastle.wav \
    img/background.jpeg \
    img/background.png \
    img/bullet.png \
    img/cannon.png \
    img/cannon2.png \
    img/cannon3.png \
    img/castle.png \
    img/castle2.png \
    img/castle3.png \
    img/enemy.png \
    img/fence.png \
    img/fence2.png \
    img/fence3.png \
    img/gameover.jpg \
    img/grass.png \
    img/ice.png \
    img/ice2.png \
    img/icon.png \
    img/settings.png \
    img/settingsWallpaper.jpg \
    img/stone.jpg \
    img/stone.png \
    img/stone.webp \
    img/stone2.png \
    img/stonebackground.png \
    img/tent.png \
    img/tent2.png \
    img/tent2.webp \
    img/tent3.png \
    img/test.jpg \
    img/winning.jpg
