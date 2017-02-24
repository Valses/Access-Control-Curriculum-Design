#ifndef BLACKCARDSET_H
#define BLACKCARDSET_H
//添加黑令牌
#include <QDialog>

#include <QMessageBox>

namespace Ui {
class BlackCardSet;
}

class BlackCardSet : public QDialog
{
    Q_OBJECT

public:
    explicit BlackCardSet(QWidget *parent = 0);
    ~BlackCardSet();

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

    void on_checkBoxr_clicked(bool checked);

    void on_checkBoxw_clicked(bool checked);

private:
    Ui::BlackCardSet *ui;
};

#endif // BLACKCARDSET_H
