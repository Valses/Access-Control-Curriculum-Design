#ifndef WITHDRAW_H
#define WITHDRAW_H
//撤销权限
#include <QDialog>

#include <QMessageBox>


namespace Ui {
class Withdraw;
}

class Withdraw : public QDialog
{
    Q_OBJECT

public:
    explicit Withdraw(QWidget *parent = 0);
    ~Withdraw();

private slots:

    void on_yesButton_clicked();

    void on_closeButton_clicked();


    void on_checkBoxr_clicked(bool checked);

    void on_checkBoxw_clicked(bool checked);

private:
    Ui::Withdraw *ui;
};

#endif // WITHDRAW_H
