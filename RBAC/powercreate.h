#ifndef POWERCREATE_H
#define POWERCREATE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class PowerCreate;
}

class PowerCreate : public QDialog
{
    Q_OBJECT

public:
    explicit PowerCreate(QWidget *parent = 0);
    ~PowerCreate();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PowerCreate *ui;
};

#endif // POWERCREATE_H
