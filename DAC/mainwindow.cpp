#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include "database.h"

extern QString globalname;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("DAC");

    QString s1 = tr("Welcome "),s2,s3 = ("!");
    s2 = globalname;
    ui->label->setText(s1+s2+s3);

    table = new QSqlTableModel(this);
    table->setTable("Object");
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table->select();
    ui->tableView->setModel(table);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table2 = new QSqlTableModel(this);
    table2->setTable("Power");
    table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table2->select();
    table2->removeColumn(0);
    ui->tableView_2->setModel(table2);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);


    table3 = new QSqlTableModel(this);
    table3->setTable("BlackList");
    table3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table3->select();
    table3->removeColumn(0);
    ui->tableView_3->setModel(table3);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_uCangeButton_clicked()
{
    this->close();
    Login lwin;
    lwin.exec();
}

void MainWindow::on_createButton_clicked()
{
    ObjCreate c;
    c.exec();
    if(!isConnection()){
        return;
    }
    table = new QSqlTableModel(this);
    table->setTable("Object");
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table->select();
    ui->tableView->setModel(table);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table2 = new QSqlTableModel(this);
    table2->setTable("Power");
    table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table2->select();
    table2->removeColumn(0);
    ui->tableView_2->setModel(table2);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);


    table3 = new QSqlTableModel(this);
    table3->setTable("BlackList");
    table3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table3->select();
    table3->removeColumn(0);
    ui->tableView_3->setModel(table3);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

void MainWindow::on_deleteButton_clicked()
{
    ObjDelete c;
    c.exec();
    if(!isConnection()){
        return;
    }
    table = new QSqlTableModel(this);
    table->setTable("Object");
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table->select();
    ui->tableView->setModel(table);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table2 = new QSqlTableModel(this);
    table2->setTable("Power");
    table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table2->select();
    table2->removeColumn(0);
    ui->tableView_2->setModel(table2);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);


    table3 = new QSqlTableModel(this);
    table3->setTable("BlackList");
    table3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table3->select();
    table3->removeColumn(0);
    ui->tableView_3->setModel(table3);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_readButton_clicked()
{
    ReadPower c;
    c.exec();
    if(!isConnection()){
        return;
    }

}

void MainWindow::on_writeButton_clicked()
{
    WritePower c;
    c.exec();
    if(!isConnection()){
        return;
    }
}

void MainWindow::on_aAuthority_clicked()
{
    Authorize c;
    c.exec();
    if(!isConnection()){
        return;
    }
    table2 = new QSqlTableModel(this);
    table2->setTable("Power");
    table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table2->select();
    table2->removeColumn(0);
    ui->tableView_2->setModel(table2);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_dAuthority_clicked()
{
    Withdraw c;
    c.exec();
    if(!isConnection()){
        return;
    }
    table2 = new QSqlTableModel(this);
    table2->setTable("Power");
    table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table2->select();
    table2->removeColumn(0);
    ui->tableView_2->setModel(table2);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_aBlackCard_clicked()
{
    BlackCardSet c;
    c.exec();
    if(!isConnection()){
        return;
    }
    table3 = new QSqlTableModel(this);
    table3->setTable("BlackList");
    table3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table3->select();
    table3->removeColumn(0);
    ui->tableView_3->setModel(table3);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_dBlackCard_clicked()
{
    BlackCardRevoke c;
    c.exec();
    if(!isConnection()){
        return;
    }
    table3 = new QSqlTableModel(this);
    table3->setTable("BlackList");
    table3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table3->select();
    table3->removeColumn(0);
    ui->tableView_3->setModel(table3);
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_clearButton_clicked()
{
    QMessageBox::StandardButton rep = QMessageBox::question(this, "warning", "确定注销用户？", QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    if(rep == QMessageBox::Yes) {
        isConnection();

        QSqlQuery query;
        query.prepare("select * from Power where GiverID = ?");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(query.isValid()){
            QMessageBox::warning(this,"Warning","请删除本用户所有授权后再注销用户!",QMessageBox::Yes);
            return;
        }
        query.prepare("delete from User where UserID = ?");
        query.addBindValue(globalname);
        query.exec();
        query.prepare("delete from Object where UserID = ?");
        query.addBindValue(globalname);
        query.exec();
        query.prepare("delete from Power where UserID = ?");
        query.addBindValue(globalname);
        query.exec();
        query.prepare("delete from BlackList where UserID = ?");
        query.addBindValue(globalname);

        query.exec();
        this->close();
        Login win;
        win.exec();
    }
}
