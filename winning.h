#ifndef WINNING_H
#define WINNING_H

#include <QDialog>

namespace Ui {
class winning;
}

class winning : public QDialog
{
    Q_OBJECT

public:
    explicit winning(QWidget *parent = nullptr);
    ~winning();

private:
    Ui::winning *ui;
};

#endif // WINNING_H
