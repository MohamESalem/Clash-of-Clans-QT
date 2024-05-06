#include "healthbar.h"
#include "game.h"
#include <QBrush>

extern Game* game;

HealthBar::HealthBar(int x, int y, int width, double health, bool blue) {
    // initialize data members
    currHealth = maxHealth = health;
    this->width = width;
    // create the colors
    QBrush gray(Qt::gray);
    QBrush green(Qt::green);
    QBrush blueColor(Qt::blue);
    // create the rectangles
    int offset = 8, height = 4;
    int final_x = x, final_y = !blue ? y - offset : y;
    setRect(final_x, final_y, width, height);
    setZValue(8);
    setBrush(gray);
    progressBar = new QGraphicsRectItem(final_x, final_y, width, height, this);
    progressBar->setZValue(9);
    if(!blue)
        progressBar->setBrush(green);
    else
        progressBar->setBrush(blueColor);
}

QGraphicsRectItem *HealthBar::getProgressBar()
{
    return progressBar;
}

int HealthBar::getCurrHealth() {
    return currHealth;
}

void HealthBar::decrementCurrHealth(int damage) {
    currHealth -= damage;
    if(currHealth < 0) currHealth = 0;
    // calculate the new width
    QBrush red(Qt::red);
    double per = currHealth/maxHealth;
    int newWidth = per * width;
    // set the new width
    QRectF rect = progressBar->rect();
    rect.setWidth(newWidth);
    progressBar->setRect(rect);
    if(per < 0.5)
        progressBar->setBrush(red);
}

void HealthBar::incrementCurrHealth(int x)
{
    currHealth += x;
    if(currHealth > maxHealth) currHealth = maxHealth;
    // calculate the new width
    QBrush green(Qt::green);
    double per = currHealth/maxHealth;
    int newWidth = per * width;
    // set the new width
    QRectF rect = progressBar->rect();
    rect.setWidth(newWidth);
    progressBar->setRect(rect);
    if(per >= 0.5)
        progressBar->setBrush(green);
}

void HealthBar::setCurrHealth(int x)
{
    currHealth = x;
    double per = currHealth/maxHealth;
    int newWidth = per * width;
    QRectF rect = progressBar->rect();
    rect.setWidth(newWidth);
    progressBar->setRect(rect);
    if(per < 0.5)
        progressBar->setBrush(Qt::red);
}

void HealthBar::show()
{
    game->getScene()->addItem(this);
}

void HealthBar::hide()
{
    game->getScene()->removeItem(this);
}

void HealthBar::move(int dx, int dy)
{
    setPos(x() + dx, y() + dy);
    // progressBar->setPos(x() + dx, y() + dy);
}

