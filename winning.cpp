#include "winning.h"
#include "ui_winning.h"

winning::winning(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::winning)
{
    ui->setupUi(this);
    setWindowTitle("You Won!");
    setWindowIcon(QIcon(":/images/img/icon.png"));
}

winning::~winning()
{
    delete ui;
}
