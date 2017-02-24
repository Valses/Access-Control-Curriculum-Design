#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QMessageBox>
#include "login.h"
#include "objcreate.h"
#include "objdelete.h"
#include "authorize.h"
#include "readpower.h"
#include "writepower.h"
#include "blackcardrevoke.h"
#include "blackcardset.h"
#include "withdraw.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int is_admin;
    QString name;

private slots:
    void on_exitButton_clicked();

    void on_uCangeButton_clicked();

    void on_createButton_clicked();

    void on_deleteButton_clicked();

    void on_readButton_clicked();

    void on_writeButton_clicked();

    void on_aAuthority_clicked();

    void on_dAuthority_clicked();

    void on_aBlackCard_clicked();

    void on_dBlackCard_clicked();

    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *table;
    QSqlTableModel *table2;
    QSqlTableModel *table3;

};

#endif // MAINWINDOW_H
