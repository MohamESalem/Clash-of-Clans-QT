#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>
#include "QPushButton"


namespace Ui {
class gameover;
}

class gameover : public QDialog
{
    Q_OBJECT

public:
    explicit gameover(QWidget *parent = nullptr);
    ~gameover();


private slots:
    void on_replayButton_clicked();

private:
    Ui::gameover *ui;
};

#endif // GAMEOVER_H
