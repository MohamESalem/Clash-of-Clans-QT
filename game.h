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
#include "workersclan.h"
#include "fence.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:
    // private data members
    QGraphicsScene* scene;
    int boardData[12][16];
    int blockUnit;
    QGraphicsPixmapItem* boardImages[12][16];
    Castle* castle;
    Cannon* cannon;
    // workers clan
    Tent* tent1;
    Tent* tent2;
    WorkersClan* group1;
    WorkersClan* group2;
    // damaged fence
    // workers
    int workersMaxCount;
    int workersAvaCount;
    bool underExec;
    //timer
    int duration;
    QTimer* gameTimer;
    QTimer* enemyTimer;
    QGraphicsTextItem* timerLabel;
    // private methods
    void readBoardData(QString path);
    void drawBoard(QString path);

public:
    Game();
    QList<Fence*> damagedFence;
    void start();
    void deleteItems();
    void gameOver();
    void showWinningWdn();
    // overload mousePressEvent and mouseMoveEvent
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    int getBlockUnit();
    Castle* getCastle();
    Cannon* getCannon();
    QGraphicsScene *getScene();
    // WorkersClan functions
    int getAvailableGroup(int x, int y);
    WorkersClan* getGroup1();
    WorkersClan* getGroup2();
    // delay
    void delay(int sec);
    void mDelay(int mSec);

    // testing data members
    Fence* testFence;
    Fence* test2;
    Fence* test3;




public slots:
    void updateTimer();
    void spawnEnemies();
};

#endif // GAME_H
