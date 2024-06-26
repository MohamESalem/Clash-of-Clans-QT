#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class HealthBar : public QGraphicsRectItem {
private:
    double maxHealth;
    double currHealth;
    int width;
    QGraphicsRectItem* progressBar;
public:
    HealthBar(int,int,int,double,bool=false);
    QGraphicsRectItem* getProgressBar();
    // ~HealthBar();
    // int getGetMaxHealth();
    int getCurrHealth();
    void decrementCurrHealth(int);
    void incrementCurrHealth(int);
    void provideShield();
    void removeShield();
    void setCurrHealth(double);
    void show();
    void hide();
    void move(int,int);
};

#endif // HEALTHBAR_H
