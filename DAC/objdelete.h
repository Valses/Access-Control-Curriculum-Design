#ifndef OBJDELETE_H
#define OBJDELETE_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class ObjDelete;
}

class ObjDelete : public QDialog
{
    Q_OBJECT

public:
    explicit ObjDelete(QWidget *parent = 0);
    ~ObjDelete();

private slots:
    void on_deleteButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::ObjDelete *ui;
};

#endif // OBJDELETE_H
