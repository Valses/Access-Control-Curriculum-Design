#ifndef PRACREATE_H
#define PRACREATE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class PRACreate;
}

class PRACreate : public QDialog
{
    Q_OBJECT

public:
    explicit PRACreate(QWidget *parent = 0);
    ~PRACreate();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::PRACreate *ui;
};

#endif // PRACREATE_H
