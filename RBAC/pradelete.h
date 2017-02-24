#ifndef PRADELETE_H
#define PRADELETE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class PRADelete;
}

class PRADelete : public QDialog
{
    Q_OBJECT

public:
    explicit PRADelete(QWidget *parent = 0);
    ~PRADelete();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PRADelete *ui;
};

#endif // PRADELETE_H
