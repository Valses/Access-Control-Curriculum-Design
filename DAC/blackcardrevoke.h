#ifndef BLACKCARDREVOKE_H
#define BLACKCARDREVOKE_H
//撤销黑令牌
#include <QDialog>

#include <QMessageBox>

namespace Ui {
class BlackCardRevoke;
}

class BlackCardRevoke : public QDialog
{
    Q_OBJECT

public:
    explicit BlackCardRevoke(QWidget *parent = 0);
    ~BlackCardRevoke();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

    void on_checkBoxc_clicked(bool checked);

private:
    Ui::BlackCardRevoke *ui;
};

#endif // BLACKCARDREVOKE_H
