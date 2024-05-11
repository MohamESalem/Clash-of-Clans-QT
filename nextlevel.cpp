#include "nextlevel.h"
#include "game.h"
#include "ui_nextlevel.h"
#include <QVBoxLayout>

extern Game *game;

nextLevel::nextLevel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::nextLevel)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/images/img/nextlevel.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    setWindowTitle("Ready for next level?");
    setWindowIcon(QIcon(":/images/img/sword.png"));
    QString bkgndStyle = "background-color: rgba(255, 255, 255, 0.2);"
                         "border-radius: 10px;"; // White color with 50% opacity
    ui->backgroundLabel->setStyleSheet(bkgndStyle);

    // Style text
    QString textStyle = "QLabel {"
                        "    font-size: 48px;"
                        "    font-weight: bold;"
                        "    font-family: 'Supercell-Magic';" // Font family similar to Clash of Clans
                        "    color: #FFFFFF;"                 // Text color
                        "}";
    ui->text->setStyleSheet(textStyle);
    ui->text->setText("To Level " + QString::number(game->getLevel() + 2));

    // Style the continue button
    QString buttonStyle = "QPushButton {"
                          "    height: 35px;"
                          "    margin-top: 25px;"
                          "    background-color: #FFD503;" // Yellow background color
                          "    color: #FFFFFF;"
                          "    font-weight: bold;"
                          "    border: none;"               // No border
                          "    border-radius: 5px;"         // Rounded corners
                          "}"
                          "QPushButton:hover {"
                          "    background-color: #E6BF00;" // Darker yellow background color on hover
                          "}";
    ui->continueButton->setStyleSheet(buttonStyle);
    ui->continueButton->setText("Continue");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(ui->text);
    layout->addWidget(ui->continueButton);
}

nextLevel::~nextLevel()
{
    delete ui;
}

void nextLevel::on_continueButton_clicked()
{
    hide();
    game->start(game->getLevel() + 1);
}

