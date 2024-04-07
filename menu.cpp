#include "menu.h"
#include "game.h"
#include "ui_menu.h"

extern Game *game;

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    this->resize(800, 600);
    QString startStyle = "QPushButton#startButton {"
                         "    background-color: #FFB901;" // Set the background color to #FFB901
                         "    border: 2px solid #FFB901;" // Set the border color to #FFB901
                         "    border-radius: 10px;"
                         "    color: white;"
                         "    font-size: 18px;"
                         "    padding: 10px 20px;"
                         "}"
                         "QPushButton#startButton:hover {"
                         "    background-color: #FFD441;" // Lighter shade of yellow for hover
                         "    border-color: #FF9E00;" // Lighter shade of yellow for hover
                         "}"
                         "QPushButton#startButton:pressed {"
                         "    background-color: #E0A800;" // Darker shade of yellow for pressed
                         "}";

    QString exitStyle = "QPushButton#exitButton {"
                    "    background-color: #FF0000;" // Red color
                    "    border: 2px solid #FF0000;" // Red color
                    "    border-radius: 10px;"
                    "    color: white;"
                    "    font-size: 18px;"
                    "    padding: 10px 20px;"
                    "}"
                    "QPushButton#exitButton:hover {"
                    "    background-color: #FF3333;" // Lighter shade of red for hover
                    "    border-color: #FF3333;" // Lighter shade of red for hover
                    "}"
                    "QPushButton#exitButton:pressed {"
                    "    background-color: #CC0000;" // Darker shade of red for pressed
                    "}";

    ui->startButton->setStyleSheet(startStyle);
    ui->exitButton->setStyleSheet(exitStyle);

    QPixmap bkgnd("D:/code/university/CSII Lab/Clash of Clans/Clash-of-Clans-QT/img/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

menu::~menu()
{
    delete ui;
}

void menu::on_startButton_clicked()
{
    hide();
    game->start();
}


void menu::on_exitButton_clicked()
{
    hide();
}

