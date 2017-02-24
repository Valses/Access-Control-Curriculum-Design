#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"
#include "signup.h"
#include "database.h"

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
    SignUp *win2;

private slots:
    void on_signInButton_clicked();

    void on_signUpButton_clicked();

    void on_uaButton_clicked();

    void on_loginWindowFinished();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
