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
#include "tent.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:
    // private data members
    QGraphicsScene* scene;
    int boardData[12][16];
    int blockUnit;
    QGraphicsPixmapItem boardImages[12][16];
    Castle* castle;
    Cannon* cannon;
    Tent* tent;
    // workers
    int workersMaxCount;
    int workersAvaCount;
    //timer
    int duration;
    QTimer* timer;
    QGraphicsTextItem* timerLabel;
    // private methods
    void readBoardData(QString path);
    void drawBoard(QString path);
    void delay(int sec);

public:
    Game();
    void start();
    // overload mousePressEvent and mouseMoveEvent
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    int getBlockUnit();
    Castle* getCastle();
    Cannon* getCannon();
    Tent* getTent();
    // workers functions
    void makeWorkers();
    void decrementWorkersMaxCount();
    void incrementWorkersAvaCount();
    void decrementWorkersAvaCount();

public slots:
    void updateTimer();
};

#endif // GAME_H
