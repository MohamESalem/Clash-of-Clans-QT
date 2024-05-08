#include "options.h"
#include "ui_options.h"
#include <QGraphicsBlurEffect>
#include <QVBoxLayout>
#include "game.h"
#include "menu.h"

extern Game *game;

options::options(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::options)
{
    ui->setupUi(this);
    setWindowTitle("Settings");
    setWindowIcon(QIcon(":/images/img/settings.png"));
    QPixmap bkgnd(":/images/img/settingsWallpaper.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    //style label
    QString bkgndStyle = "background-color: rgba(255, 255, 255, 128);"
                         "border-radius: 10px;"; // White color with 50% opacity
    ui->backgroundLabel->setStyleSheet(bkgndStyle);
    ui->volumeSlider->setSliderPosition(50);

}


options::~options()
{
    delete ui;
}

void options::on_discardButton_clicked()
{
    hide();
}


void options::on_saveButton_clicked()
{
    double volumeValue = ui->volumeSlider->value();
    game->setVolume(volumeValue);
    hide();
    menu *m = new menu;
    m->show();
}

