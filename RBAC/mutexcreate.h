#ifndef MUTEXCREATE_H
#define MUTEXCREATE_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class MutexCreate;
}

class MutexCreate : public QDialog
{
    Q_OBJECT

public:
    explicit MutexCreate(QWidget *parent = 0);
    ~MutexCreate();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MutexCreate *ui;
};

#endif // MUTEXCREATE_H
