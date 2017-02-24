#ifndef READPOWER_H
#define READPOWER_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ReadPower;
}

class ReadPower : public QDialog
{
    Q_OBJECT

public:
    explicit ReadPower(QWidget *parent = 0);
    ~ReadPower();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::ReadPower *ui;
};

#endif // READPOWER_H
