#ifndef WRITEPOWER_H
#define WRITEPOWER_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class WritePower;
}

class WritePower : public QDialog
{
    Q_OBJECT

public:
    explicit WritePower(QWidget *parent = 0);
    ~WritePower();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::WritePower *ui;
};

#endif // WRITEPOWER_H
