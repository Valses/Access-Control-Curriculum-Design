#include "readpower.h"
#include "ui_readpower.h"
#include "database.h"

extern QString globalname;

ReadPower::ReadPower(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadPower)
{
    ui->setupUi(this);
    this->setWindowTitle("读客体");
}

ReadPower::~ReadPower()
{
    delete ui;
}

void ReadPower::on_yesButton_clicked()
{
    if(ui->ObjName->text() == "")
    {
        QMessageBox::warning(this,tr("Warning"),tr("请输入客体名称!"),QMessageBox::Yes);
        ui->ObjName->clear();
        ui->ObjName->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from Object where ObjID = ? ");
    query.addBindValue(ui->ObjName->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,tr("Warning"),tr("客体不存在!"),QMessageBox::Yes);
        ui->ObjName->clear();
        ui->ObjName->setFocus();
        return;
    }

    query.prepare("select * from Object where ObjID = ? and UserID = ?");
    query.addBindValue(ui->ObjName->text());
    query.addBindValue(globalname);
    query.exec();
    query.next();
    if(query.isValid()){
        //可以读
        QMessageBox::warning(this,"Congratulations","读客体成功!",QMessageBox::Yes);
    }
    else{
        query.prepare("select * from BlackList where UserID = ? and ObjID = ? and noAbility= ?");
        query.addBindValue(globalname);
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("r");
        query.exec();
        query.next();
        if(query.isValid()){
            QMessageBox::warning(this,"Warning","存在黑令牌，无权限读该客体!",QMessageBox::Yes);
        }
        else{
            query.prepare("select * from Power where UserID = ? and ObjID = ? and Ability= ?");
            query.addBindValue(globalname);
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("r");
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Congratulations","读客体成功!",QMessageBox::Yes);
            }
            else{
                //不可读
                QMessageBox::warning(this,"Warning","无权限读该客体!",QMessageBox::Yes);
            }
        }

    }
    this->close();
}

void ReadPower::on_closeButton_clicked()
{
    this->close();
}
