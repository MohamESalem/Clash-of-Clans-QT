#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include "castle.h"
#include "cannon.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:
    QGraphicsScene* scene;
    int boardData[12][16];
    int blockUnit;
    QGraphicsPixmapItem boardImages[12][16];
    Castle* castle;
    Cannon* cannon;
    void readBoardData(QString path);
    void drawBoard(QString path);
public:
    Game();
    void start();
    int getBlockUnit();
    Castle* getCastle();
    Cannon* getCannon();
};

#endif // GAME_H
