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
#include "graph.h"
#include "enemy.h"

class Game : public QGraphicsView
{
    Q_OBJECT
private:
    // private data members
    int level;
    QGraphicsScene* scene;
    int boardData[12][16];
    int blockUnit;
    int bonusDefaultDuration;
    QGraphicsPixmapItem* boardImages[12][16];
    Castle* castle;
    Cannon* cannon;
    int castleHealth;
    bool isBulletBonus;
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
    int bonusDuration;
    QTimer* gameTimer;
    QTimer* enemyTimer;
    QTimer* giftTimer;
    QTimer* bonusTimer;
    QGraphicsTextItem* timerLabel;
    QGraphicsTextItem* bonusTimerLabel;
    QList<int> startEnemy;
    QList<int> startGift;
    // private methods
    void readBoardData(QString path);
    void drawBoard(QString path);

public:
    Game();
    QList<Fence*> damagedFence;
    void start(int);
    void startNewLevel();
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
    int getLevel();
    // WorkersClan functions
    int getAvailableGroup(int,int);
    WorkersClan* getGroup1();
    WorkersClan* getGroup2();
    // delay
    void delay(int); // delay in seconds
    void mDelay(int); // delay in milliseconds

    // testing data members
    Fence* testFence;
    Fence* test2;
    Fence* test3;
    // graph functions
    Graph* graph;
    void makeGraph();
    void updateEnemyPath();
    QList<Enemy*> enemies;
    // gifts functions
    void shieldCastle();
    void doubleBullets();
    //audio
    int volume;
    void playSound(QUrl url);



public slots:
    void updateTimer();
    void spawnEnemies();
    void updateBonusTimer();
    void randGifts();
};

#endif // GAME_H
