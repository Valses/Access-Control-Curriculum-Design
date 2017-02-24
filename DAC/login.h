#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include "usercreate.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    MainWindow *win1;
    UserCreate *win2;

private slots:

    void on_sign_in_clicked();
    void on_sign_up_clicked();
    void on_loginWindowFinished();


private:
    Ui::Login *ui;
};

#endif // LOGIN_H
