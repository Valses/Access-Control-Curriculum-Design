#include "writepower.h"
#include "ui_writepower.h"

#include "database.h"

extern QString globalname;

WritePower::WritePower(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WritePower)
{
    ui->setupUi(this);
    this->setWindowTitle("写客体");
}

WritePower::~WritePower()
{
    delete ui;
}

void WritePower::on_yesButton_clicked()
{
    if(ui->ObjName->text() == ""){
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
        //拥有者，可以写
        QMessageBox::warning(this,"Congratulations","写客体成功!",QMessageBox::Yes);
        this->close();
    }
    else{
        //非拥有者
        query.prepare("select * from BlackList where UserID = ? and ObjID = ? and noAbility= ?");
        query.addBindValue(globalname);
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("w");
        query.exec();
        query.next();
        if(query.isValid()){
            QMessageBox::warning(this,"Warning","存在黑令牌，无权限写该客体!",QMessageBox::Yes);
        }
        else{
            query.prepare("select * from Power where UserID = ? and ObjID = ? and Ability= ?");
            query.addBindValue(globalname);
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("w");
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Congratulations","写客体成功!",QMessageBox::Yes);
            }
            else{
                //不可写
                QMessageBox::warning(this,"Warning","无权限写该客体!",QMessageBox::Yes);
            }
        }

    }
    this->close();
}

void WritePower::on_closeButton_clicked()
{
    this->close();
}
