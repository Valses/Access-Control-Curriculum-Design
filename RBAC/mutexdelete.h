#ifndef MUTEXDELETE_H
#define MUTEXDELETE_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class MutexDelete;
}

class MutexDelete : public QDialog
{
    Q_OBJECT

public:
    explicit MutexDelete(QWidget *parent = 0);
    ~MutexDelete();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MutexDelete *ui;
};

#endif // MUTEXDELETE_H
