#include "options.h"
#include "ui_options.h"
#include <QGraphicsBlurEffect>
#include <QVBoxLayout>
#include "game.h"
#include "menu.h"
#include <cstdlib>


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
    ui->volumeSlider->setSliderPosition(game->getIsVolSet() ? game->getVolume()  * 115 : 50);
    //style volume label
    QString labelStyle = "color: black;"
                         "font-weight: bold;";
    ui->volumeLabel->setStyleSheet(labelStyle);
    ui->volumeSlider->setStyleSheet(".QSlider {"
                                    "    min-height: 34px;"
                                    "    max-height: 34px;"
                                    "}"
                                    "QSlider::groove:horizontal {"
                                    "    border: 1px solid #262626;"
                                    "    height: 8px;"
                                    "    background: #393939;"
                                    "    margin: 0px 1px;"
                                    "    border-radius: 5px;"
                                    "}"
                                    "QSlider::handle:horizontal {"
                                    "    background: #009893;"
                                    "    border: 1px solid white;"
                                    "    width: 15px;"
                                    "    height: 100px;"
                                    "    margin: -12px -6px;"
                                    "    border-radius: 5px;"
                                    "}"
                                    "QSlider::add-page:qlineargradient {"
                                    "    background: #f6fcff;"
                                    "    border-top-right-radius: 5px;"
                                    "    border-bottom-right-radius: 5px;"
                                    "    border-top-left-radius: 0px;"
                                    "    border-bottom-left-radius: 0px;"
                                    "}"
                                    "QSlider::sub-page:qlineargradient {"
                                    "    background: #0c2038;"
                                    "    border-top-right-radius: 0px;"
                                    "    border-bottom-right-radius: 0px;"
                                    "    border-top-left-radius: 5px;"
                                    "    border-bottom-left-radius: 5px;"
                                    "}");
    ui->mapsLabel->setStyleSheet(labelStyle);
    ui->saveButton->setStyleSheet("background-color: #FFB901; color: white; font-weight: bold;");
    ui->discardButton->setStyleSheet("background-color: #FF0000; color: white; font-weight: bold;");

    QString radio1 = "QRadioButton::indicator {"
                     "    width: 240px;"
                     "    height: 115px;"
                     "    background-image: url(:/images/img/optionsMaps/green.png);"
                     "    background-repeat: no-repeat;"
                     "    border-radius: 15px;"
                     "}"
                     "QRadioButton::indicator::checked {"
                     "border: 2.5px solid purple;"
                     "}";
    QString radio2 = "QRadioButton::indicator {"
                     "    width: 240px;"
                     "    height: 115px;"
                     "    background-image: url(:/images/img/optionsMaps/ice.png);"
                     "    background-repeat: no-repeat;"
                     "    border-radius: 15px;"
                     "}"
                     "QRadioButton::indicator::checked {"
                     "border: 2.5px solid purple;"
                     "}";
    QString radio3 = "QRadioButton::indicator {"
                     "    width: 240px;"
                     "    height: 115px;"
                     "    background-image: url(:/images/img/optionsMaps/stone.png);"
                     "    background-repeat: no-repeat;"
                     "    border-radius: 15px;"
                     "}"
                     "QRadioButton::indicator::checked {"
                     "border: 2.5px solid purple;"
                     "}";
    QString radio4 = "QRadioButton::indicator {"
                     "    width: 240px;"
                     "    height: 115px;"
                     "    background-image: url(:/images/img/settingsWallpaper.jpg);" //! ?
                     "    background-repeat: no-repeat;"
                     "    border-radius: 15px;"
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
    if(!game->getIsMapSet()) {
        buttonGroup->buttons().first()->setChecked(true);
    } else {
        if(game->getRandMap()) ui->radioButton_4->setChecked(true);
        else if(game->getMap() == 1) ui->radioButton->setChecked(true);
        else if(game->getMap() == 2) ui->radioButton_3->setChecked(true);
        else if(game->getMap() == 3) ui->radioButton_2->setChecked(true);
    }

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
    int map = buttonGroup->checkedId();;
    if(map == -2)
        game->setMap(1), game->setRandMap(false);
    else if(map == -3)
        game->setMap(3), game->setRandMap(false);
    else if(map == -4)
        game->setMap(2), game->setRandMap(false);
    else if(map == -5)
    {
        int randomMap = rand() % 3 + 1;
        game->setRandMap(true);
        game->setMap(randomMap);
    }
    hide();
    menu *m = new menu;
    m->show();
}

