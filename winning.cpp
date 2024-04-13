#include "winning.h"
#include "ui_winning.h"

winning::winning(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::winning)
{
    ui->setupUi(this);
}

winning::~winning()
{
    delete ui;
}
