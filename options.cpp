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
    ui->volumeSlider->setSliderPosition(game->getIsVolSet() ? game->getVolume()  * 100 : 50);
    //style volume label
    QString labelStyle = "color: black;"
                         "font-weight: bold;";
    ui->volumeLabel->setStyleSheet(labelStyle);
    ui->mapsLabel->setStyleSheet(labelStyle);
    ui->saveButton->setStyleSheet("background-color: #FFB901; color: white; font-weight: bold;");
    ui->discardButton->setStyleSheet("background-color: #FF0000; color: white; font-weight: bold;");

    QString radio1 = "QRadioButton::indicator {"
                     "    width: 150px;"
                     "    height: 100px;"
                     "    background-image: url(:/images/img/settingsWallpaper.jpg);"
                     "    background-repeat: no-repeat;"
                     "    border-radius: 15px;"
                     "    background-position: center;"
                     "}"
                     "QRadioButton::indicator::checked {"
                     "border: 2.5px solid purple;"
                     "}";
    QString radio2 = "QRadioButton::indicator {"
                     "    width: 150px;"
                     "    height: 100px;"
                     "    background-image: url(:/images/img/settingsWallpaper.jpg);"
                     "    background-repeat: no-repeat;"
                     "    border-radius: 15px;"
                     "    background-position: center;"
                     "}"
                     "QRadioButton::indicator::checked {"
                     "border: 2.5px solid purple;"
                     "}";
    QString radio3 = "QRadioButton::indicator {"
                     "    width: 150px;"
                     "    height: 100px;"
                     "    background-image: url(:/images/img/settingsWallpaper.jpg);"
                     "    background-repeat: no-repeat;"
                     "    border-radius: 15px;"
                     "    background-position: center;"
                     "}"
                     "QRadioButton::indicator::checked {"
                     "border: 2.5px solid purple;"
                     "}";
    QString radio4 = "QRadioButton::indicator {"
                     "    width: 150px;"
                     "    height: 100px;"
                     "    background-image: url(:/images/img/settingsWallpaper.jpg);"
                     "    background-repeat: no-repeat;"
                     "    border-radius: 15px;"
                     "    background-position: center;"
                     "}"
                     "QRadioButton::indicator::checked {"
                     "border: 2.5px solid purple;"
                     "}";
    ui->radioButton->setStyleSheet(radio1);
    ui->radioButton_2->setStyleSheet(radio2);
    ui->radioButton_3->setStyleSheet(radio3);
    ui->radioButton_4->setStyleSheet(radio4);
    ui->radioButton->setText("");
    ui->radioButton_2->setText("");
    ui->radioButton_3->setText("");
    ui->radioButton_4->setText("");

    // radio group
    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(ui->radioButton);
    buttonGroup->addButton(ui->radioButton_2);
    buttonGroup->addButton(ui->radioButton_3);
    buttonGroup->addButton(ui->radioButton_4);
    buttonGroup->buttons().first()->setChecked(true);

}


options::~options()
{
    delete ui;
}

void options::on_discardButton_clicked()
{
    hide();
    menu *m = new menu;
    m->show();
}


void options::on_saveButton_clicked()
{
    double volumeValue = ui->volumeSlider->value();
    game->setVolume(volumeValue);
    // buttons IDs are -2, -3, -4, -5 clockwise
    // qDebug() << buttonGroup->checkedId();
    hide();
    menu *m = new menu;
    m->show();
}

