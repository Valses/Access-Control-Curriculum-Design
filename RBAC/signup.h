#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include "database.h"
namespace Ui {
class
        SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = 0);
    ~SignUp();

private slots:
    void on_pushButton_clicked();

signals:
    void on_loginWindowFinishedSignal();


private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
