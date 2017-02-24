#ifndef OBJCREATE_H
#define OBJCREATE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ObjCreate;
}

class ObjCreate : public QDialog
{
    Q_OBJECT

public:
    explicit ObjCreate(QWidget *parent = 0);
    ~ObjCreate();

private slots:
    void on_createButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::ObjCreate *ui;
};

#endif // OBJCREATE_H
