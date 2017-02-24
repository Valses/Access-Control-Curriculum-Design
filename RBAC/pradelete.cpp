#include "pradelete.h"
#include "ui_pradelete.h"
#include "database.h"
PRADelete::PRADelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PRADelete)
{
    ui->setupUi(this);
}

PRADelete::~PRADelete()
{
    delete ui;
}

void PRADelete::on_yesButton_clicked()
{
    if(ui->roleEdit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入角色名称!",QMessageBox::Yes);
        ui->roleEdit->setFocus();
        return;
    }
    if(ui->powerEdit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入权限名称!",QMessageBox::Yes);
        ui->powerEdit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from Role where Role = ? ");
    query.addBindValue(ui->roleEdit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","角色不存在!",QMessageBox::Yes);
        ui->roleEdit->clear();
        ui->powerEdit->clear();
        ui->roleEdit->setFocus();
        return;
    }
    query.prepare("select * from Power where Power = ? ");
    query.addBindValue(ui->powerEdit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","权限不存在!",QMessageBox::Yes);
        ui->powerEdit->clear();
        ui->powerEdit->setFocus();
        return;
    }
    query.prepare("select * from PR where Role = ? and Power = ?");
    query.addBindValue(ui->roleEdit->text());
    query.addBindValue(ui->powerEdit->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","指派不存在!",QMessageBox::Yes);
        ui->powerEdit->clear();
        ui->roleEdit->clear();
        ui->roleEdit->setFocus();
        return;
    }
    query.prepare("delete from PR where Role = ? and Power = ?");
    query.addBindValue(ui->roleEdit->text());
    query.addBindValue(ui->powerEdit->text());
    query.exec();
    QMessageBox::warning(this, "Congratulations","用户角色指派已删除!", QMessageBox::Yes);
    accept();
}

void PRADelete::on_closeButton_clicked()
{
    this->close();
}
