#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_startButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::menu *ui;
};

#endif // MENU_H
