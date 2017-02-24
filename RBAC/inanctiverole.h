#ifndef INANCTIVEROLE_H
#define INANCTIVEROLE_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class InanctiveRole;
}

class InanctiveRole : public QDialog
{
    Q_OBJECT

public:
    explicit InanctiveRole(QWidget *parent = 0);
    ~InanctiveRole();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::InanctiveRole *ui;
};

#endif // INANCTIVEROLE_H
