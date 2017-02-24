#ifndef RHDELETE_H
#define RHDELETE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class RHDelete;
}

class RHDelete : public QDialog
{
    Q_OBJECT

public:
    explicit RHDelete(QWidget *parent = 0);
    ~RHDelete();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::RHDelete *ui;
};

#endif // RHDELETE_H
