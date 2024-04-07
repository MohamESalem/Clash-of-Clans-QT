#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QFile>
#include <QTimer>
#include <QTextStream>
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
    //timer
    int duration;
    QTimer* timer;
    QGraphicsTextItem* timerLabel;

public:
    Game();
    void start();
    // overload mousePressEven
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    int getBlockUnit();
    Castle* getCastle();
    Cannon* getCannon();


public slots:
    void updateTimer();
};

#endif // GAME_H
