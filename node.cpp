#include "node.h"


Node::Node(int x, int y, int strength)
{
    this->x =x;
    this->y =y;
    this->strength =strength;
    yPos = (x*50) + 25;
    xPos = (y*50) + 25;
}

void Node::setX(int x)
{
    this->x =x;
}

void Node::setY(int y)
{
    this->y =y;
}

void Node::setStrength(int strength)
{
    this->strength =strength;
}

int Node::getX() const
{
    return x;
}

int Node::getY() const
{
    return y;
}

int Node::getStrength() const
{
    return strength;
}

void Node::setXPos(int x)
{
    xPos = x;
}

void Node::setYPos(int y)
{
    yPos = y;
}

int Node::getYPos() const
{
    return yPos;
}

int Node::getXPos() const
{
    return xPos;
}


