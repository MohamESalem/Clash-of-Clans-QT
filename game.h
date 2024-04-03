#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Game : public QGraphicsView
{
    Q_OBJECT
private:
    QGraphicsScene* scene;
public:
    Game();
    void start();
};

#endif // GAME_H
