#include "winning.h"
#include "ui_winning.h"
#include "game.h"
extern Game* game;


winning::winning(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::winning)
{
    ui->setupUi(this);
    setWindowTitle("You Won!");
    setWindowIcon(QIcon(":/images/img/icon.png"));
    //bkgnd stlying
    QPixmap bkgnd(":/images/img/winning.jpg");

    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    //style button
    ui->replayButton->setStyleSheet("QPushButton {"
                                    "    background-color: #FFD503;" // Yellow background color
                                    "    color: #FFFFFF;"
                                    "font-weight: bold;"
                                    "    border: none;"               // No border
                                    "    border-radius: 5px;"         // Rounded corners
                                    "}"
                                    "QPushButton:hover {"
                                    "    background-color: #E6BF00;" // Darker yellow background color on hover
                                    "}");
    ui->victorLabel->setStyleSheet("QLabel {"
                                   "    font-size: 48px;"
                                   "    font-weight: bold;"
                                   "    font-family: 'Supercell-Magic';" // Font family similar to Clash of Clans
                                   "    color: #FFFFFF;"                 // Text color
                                   "}");


}

winning::~winning()
{
    delete ui;
}

void winning::on_replayButton_clicked()
{
    close();
    game->start(0);
}

