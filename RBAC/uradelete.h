#ifndef URADELETE_H
#define URADELETE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class URADelete;
}

class URADelete : public QDialog
{
    Q_OBJECT

public:
    explicit URADelete(QWidget *parent = 0);
    ~URADelete();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::URADelete *ui;
};

#endif // URADELETE_H
