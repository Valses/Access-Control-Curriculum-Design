#include "mutexcreate.h"
#include "ui_mutexcreate.h"
#include "database.h"
#include <QDebug>

MutexCreate::MutexCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MutexCreate)
{
    ui->setupUi(this);
    this->setWindowTitle("互斥添加");
}

MutexCreate::~MutexCreate()
{
    delete ui;
}

void MutexCreate::on_yesButton_clicked()
{
    if(ui->role1Edit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入角色一名称!",QMessageBox::Yes);
        ui->role1Edit->setFocus();
        return;
    }
    if(ui->role2Edit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入角色二名称!",QMessageBox::Yes);
        ui->role2Edit->setFocus();
        return;
    }
    if(ui->role2Edit->text() == ui->role1Edit->text()){
        QMessageBox::warning(this,"Warning","请重新输入!",QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query, query2;
    query.prepare("select * from Role where Role = ? ");
    query.addBindValue(ui->role1Edit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","角色一不存在!",QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }
    query.prepare("select * from Role where Role = ? ");
    query.addBindValue(ui->role2Edit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","角色二不存在!",QMessageBox::Yes);
        ui->role2Edit->clear();
        ui->role2Edit->setFocus();
        return;
    }
    query.prepare("select * from Mutex where Role= ? and Role2 = ?");
    query.addBindValue(ui->role1Edit->text());
    query.addBindValue(ui->role2Edit->text());
    query.exec();
    query.next();
    query2.prepare("select * from Mutex where Role= ? and Role2 = ?");
    query2.addBindValue(ui->role2Edit->text());
    query2.addBindValue(ui->role1Edit->text());
    query2.exec();
    query2.next();
    if(query.isValid() || query2.isValid() ){
        QMessageBox::warning(this, "Warning","互斥已存在!", QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }
    else{
        int num = 1;
        query.exec("select * from Mutex");
        if(query.last()){
            num = query.value(0).toInt();
            num++;
        }
        qDebug() << num;
        query.prepare("insert into Mutex (ID, Role, Role2) values(?, ?, ?)");
        query.addBindValue(num);
        query.addBindValue(ui->role1Edit->text());
        query.addBindValue(ui->role2Edit->text());
        query.exec();
        QMessageBox::warning(this, "Congratulations","互斥已添加!", QMessageBox::Yes);
        accept();
    }
}

void MutexCreate::on_closeButton_clicked()
{
    this->close();
}
