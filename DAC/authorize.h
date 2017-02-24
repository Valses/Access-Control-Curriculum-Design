#ifndef AUTHORIZE_H
#define AUTHORIZE_H
//授权
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Authorize;
}

class Authorize : public QDialog
{
    Q_OBJECT

public:
    explicit Authorize(QWidget *parent = 0);
    ~Authorize();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

    void on_checkBoxc_clicked(bool checked);

private:
    Ui::Authorize *ui;
};

#endif // AUTHORIZE_H
