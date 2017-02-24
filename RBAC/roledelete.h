#ifndef ROLEDELETE_H
#define ROLEDELETE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include "database.h"

namespace Ui {
class RoleDelete;
}

class RoleDelete : public QDialog
{
    Q_OBJECT

public:
    explicit RoleDelete(QWidget *parent = 0);
    ~RoleDelete();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::RoleDelete *ui;
};

#endif // ROLEDELETE_H
