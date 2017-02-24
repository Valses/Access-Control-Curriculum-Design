#include "inanctiverole.h"
#include "ui_inanctiverole.h"
#include "database.h"

extern QString globalname;

InanctiveRole::InanctiveRole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InanctiveRole)
{
    ui->setupUi(this);
    this->setWindowTitle("取消激活角色");
}

InanctiveRole::~InanctiveRole()
{
    delete ui;
}

void InanctiveRole::on_yesButton_clicked()
{
    if(ui->lineEdit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入角色名称!",QMessageBox::Yes);
        ui->lineEdit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from Role where Role= ? ");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","角色不存在!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }
    query.prepare("select * from UR where User = ? and Role= ?  ");
    query.addBindValue(globalname);
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","角色不属于该用户!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }
    query.prepare("select * from ActiveU where User = ? and Role= ?  ");
    query.addBindValue(globalname);
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","角色未激活!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }
    query.prepare("delete from ActiveU where User = ? and Role= ?  ");
    query.addBindValue(globalname);
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    QMessageBox::warning(this, "Congratulations","角色激活已删除!", QMessageBox::Yes);
    accept();
}

void InanctiveRole::on_closeButton_clicked()
{
    this->close();
}
