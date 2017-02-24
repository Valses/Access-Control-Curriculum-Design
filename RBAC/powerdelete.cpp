#include "powerdelete.h"
#include "ui_powerdelete.h"
#include "database.h"
PowerDelete::PowerDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PowerDelete)
{
    ui->setupUi(this);
    this->setWindowTitle("删除权限");
}

PowerDelete::~PowerDelete()
{
    delete ui;

}

void PowerDelete::on_yesButton_clicked()
{
    if(ui->lineEdit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入权限名称!",QMessageBox::Yes);
        ui->lineEdit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from Power where Power= ? ");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","权限不存在!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }
    query.prepare("delete from Power where Power = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.prepare("delete from PR where Power = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    QMessageBox::warning(this,"Congratulations","权限已删除!",QMessageBox::Yes);
    accept();
}

void PowerDelete::on_closeButton_clicked()
{
    this->close();
}
