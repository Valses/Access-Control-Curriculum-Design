#ifndef USERCREATE_H
#define USERCREATE_H

#include <QDialog>
#include <QMessageBox>


namespace Ui {
class UserCreate;
}

class UserCreate : public QDialog
{
    Q_OBJECT

public:
    explicit UserCreate(QWidget *parent = 0);
    ~UserCreate();

signals:
    void on_loginWindowFinishedSignal();

private slots:
    void on_pushButton_clicked();

private:
    Ui::UserCreate *ui;
};

#endif // USERCREATE_H
