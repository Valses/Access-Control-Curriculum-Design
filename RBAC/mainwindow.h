#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QSqlTableModel>
#include <QTreeView>
#include <QTreeWidget>

#include "rolecreate.h"
#include "roledelete.h"
#include "powercreate.h"
#include "powerdelete.h"
#include "mutexcreate.h"
#include "mutexdelete.h"
#include "uracreate.h"
#include "uradelete.h"
#include "pracreate.h"
#include "pradelete.h"
#include "rhcreate.h"
#include "rhdelete.h"
#include "activaterole.h"
#include "conversation.h"
#include "inanctiverole.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setAdmin(bool);
    void drawTree();
    QTreeWidgetItem *item[100];

private slots:
    void on_creRolButton_clicked();

    void on_delRolButton_clicked();

    void on_crePowButton_clicked();

    void on_delPowButton_clicked();

    void on_uChangeButton_clicked();

    void on_clearButton_clicked();

    void on_exitButton_clicked();

    void on_urButton_clicked();

    void on_durButton_clicked();

    void on_rpButton_clicked();

    void on_drpButton_clicked();

    void on_rrButton_clicked();

    void on_drrButton_clicked();

    void on_rhButton_clicked();

    void on_drhButton_clicked();

    void on_activateButton_clicked();

    void on_sButton_clicked();

    void on_inactiveButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlTableModel *table1;
    QSqlTableModel *table2;
    QSqlTableModel *table3;
    QSqlTableModel *table4;
    QSqlTableModel *table5;
    QSqlTableModel *table6;
    QSqlTableModel *table7;
    QSqlTableModel *table8;
    QTreeWidgetItem *tree;

};

#endif // MAINWINDOW_H
