#include "gameover.h"
#include "game.h"
#include "ui_gameover.h"

extern Game* game;

gameover::gameover(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::gameover)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/images/img/gameover.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    //replay button
    ui->replayButton->setStyleSheet("QPushButton {"
                         "    background-color: #262626;" // Dark background color
                         "    color: #FFFFFF;"             // Text color
                         "    border: none;"               // No border
                         "    border-radius: 5px;"         // Rounded corners
                         "}"
                         "QPushButton:hover {"
                         "    background-color: #505050;" // Darker background color on hover
                         "}");
    setWindowTitle("Game Over!");
    setWindowIcon(QIcon(":/images/img/icon.png"));
}

gameover::~gameover()
{
    delete ui;
}

void gameover::on_replayButton_clicked()
{
    close();
    game->start(0);
}

