#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class options;
}

class options : public QDialog
{
    Q_OBJECT

public:
    explicit options(QWidget *parent = nullptr);
    ~options();

private slots:
    void on_discardButton_clicked();

    void on_saveButton_clicked();

private:
    QButtonGroup *buttonGroup;
    Ui::options *ui;
};

#endif // OPTIONS_H
