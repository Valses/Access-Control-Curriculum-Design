#ifndef ROLECREATE_H
#define ROLECREATE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include "database.h"


namespace Ui {
class RoleCreate;
}

class RoleCreate : public QDialog
{
    Q_OBJECT

public:
    explicit RoleCreate(QWidget *parent = 0);
    ~RoleCreate();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::RoleCreate *ui;
};

#endif // ROLECREATE_H
