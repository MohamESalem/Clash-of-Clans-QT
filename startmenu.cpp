#include "startmenu.h"
#include "game.h"
#include "ui_startmenu.h"

extern Game *game;

startMenu::startMenu()
{
    ui->setupUi(this);
    // QString style = "QPushButton#startButton {"
    //                 "    background-color: #4CAF50;"
    //                 "    border: 2px solid #4CAF50;"
    //                 "    border-radius: 10px;"
    //                 "    color: white;"
    //                 "    font-size: 18px;"
    //                 "    padding: 10px 20px;"
    //                 "}"
    //                 "QPushButton#startButton:hover {"
    //                 "    background-color: #45a049;"
    //                 "    border-color: #45a049;"
    //                 "}"
    //                 "QPushButton#startButton:pressed {"
    //                 "    background-color: #4CAF50;"
    //                 "}";
    // ui->startButton->setStyleSheet(style);
}

startMenu::~startMenu()
{
    delete ui;
}
