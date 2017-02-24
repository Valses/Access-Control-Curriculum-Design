#include "pracreate.h"
#include "ui_pracreate.h"
#include "database.h"
PRACreate::PRACreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PRACreate)
{
    ui->setupUi(this);
}

PRACreate::~PRACreate()
{
    delete ui;
}

void PRACreate::on_yesButton_clicked()
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
    if(query.isValid()){
        QMessageBox::warning(this, "Warning","指派已存在!", QMessageBox::Yes);
        ui->roleEdit->clear();
        ui->powerEdit->clear();
        ui->roleEdit->setFocus();
        return;
    }
    else{
        int num = 1;
        query.exec("select * from PR");
        if(query.last()){
            num = query.value(0).toInt();
            num++;
        }
        qDebug() << num;
        query.prepare("insert into PR (ID, Role, Power) values(?, ?, ?)");
        query.addBindValue(num);
        query.addBindValue(ui->roleEdit->text());
        query.addBindValue(ui->powerEdit->text());
        query.exec();
        QMessageBox::warning(this, "Congratulations","角色权限指派已添加!", QMessageBox::Yes);
        accept();
    }

}

void PRACreate::on_closeButton_clicked()
{
    this->close();
}
