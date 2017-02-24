#include "mutexdelete.h"
#include "ui_mutexdelete.h"
#include "database.h"
MutexDelete::MutexDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MutexDelete)
{
    ui->setupUi(this);
    this->setWindowTitle("互斥删除");
}

MutexDelete::~MutexDelete()
{
    delete ui;
}

void MutexDelete::on_yesButton_clicked()
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
    if(query.isValid()){
        query.prepare("delete from Mutex where Role= ? and Role2 = ?");
        query.addBindValue(ui->role1Edit->text());
        query.addBindValue(ui->role2Edit->text());
        query.exec();
        QMessageBox::warning(this, "Congratulations","互斥已删除!", QMessageBox::Yes);
        accept();
    }
    else{
        query.prepare("select * from Mutex where Role= ? and Role2 = ?");
        query.addBindValue(ui->role2Edit->text());
        query.addBindValue(ui->role1Edit->text());
        query.exec();
        query.next();
        if(query.isValid()){
            query.prepare("delete from Mutex where Role= ? and Role2 = ?");
            query.addBindValue(ui->role2Edit->text());
            query.addBindValue(ui->role1Edit->text());
            query.exec();
            QMessageBox::warning(this,  "Congratulations","互斥已删除!", QMessageBox::Yes);
            accept();
        }
        else{
            QMessageBox::warning(this, "Warning","互斥不存在!", QMessageBox::Yes);
        }
    }

}

void MutexDelete::on_closeButton_clicked()
{
    this->close();
}
