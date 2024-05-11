#ifndef NEXTLEVEL_H
#define NEXTLEVEL_H

#include <QDialog>

namespace Ui {
class nextLevel;
}

class nextLevel : public QDialog
{
    Q_OBJECT

public:
    explicit nextLevel(QWidget *parent = nullptr);
    ~nextLevel();

private slots:
    void on_continueButton_clicked();

private:
    Ui::nextLevel *ui;
};

#endif // NEXTLEVEL_H
