#ifndef URACREATE_H
#define URACREATE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class URACreate;
}

class URACreate : public QDialog
{
    Q_OBJECT

public:
    explicit URACreate(QWidget *parent = 0);
    ~URACreate();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::URACreate *ui;
};

#endif // URACREATE_H
