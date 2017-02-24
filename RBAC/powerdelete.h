#ifndef POWERDELETE_H
#define POWERDELETE_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "database.h"

namespace Ui {
class PowerDelete;
}

class PowerDelete : public QDialog
{
    Q_OBJECT

public:
    explicit PowerDelete(QWidget *parent = 0);
    ~PowerDelete();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PowerDelete *ui;
};

#endif // POWERDELETE_H
