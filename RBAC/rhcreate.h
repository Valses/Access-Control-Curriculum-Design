#ifndef RHCREATE_H
#define RHCREATE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
namespace Ui {
class RHCreate;
}

class RHCreate : public QDialog
{
    Q_OBJECT

public:
    explicit RHCreate(QWidget *parent = 0);
    ~RHCreate();
    bool findLoop(QString fa, QString cd);
    void addRHList(QString fa, QString cd);

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::RHCreate *ui;
};

#endif // RHCREATE_H
