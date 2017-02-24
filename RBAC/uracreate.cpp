#include "uracreate.h"
#include "ui_uracreate.h"

#include "database.h"

URACreate::URACreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::URACreate)
{
    ui->setupUi(this);
    this->setWindowTitle("用户角色指派创建");
}

URACreate::~URACreate()
{
    delete ui;
}

void URACreate::on_yesButton_clicked()
{
    if(ui->userEdit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入用户名称!",QMessageBox::Yes);
        ui->userEdit->setFocus();
        return;
    }
    if(ui->roleEdit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入角色名称!",QMessageBox::Yes);
        ui->roleEdit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from User where UserID = ? ");
    query.addBindValue(ui->userEdit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","用户不存在!",QMessageBox::Yes);
        ui->userEdit->clear();
        ui->roleEdit->clear();
        ui->userEdit->setFocus();
        return;
    }
    query.prepare("select * from Role where Role = ? ");
    query.addBindValue(ui->roleEdit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","角色不存在!",QMessageBox::Yes);
        ui->roleEdit->clear();
        ui->roleEdit->setFocus();
        return;
    }
    query.prepare("select * from UR where User = ? and Role = ?");
    query.addBindValue(ui->userEdit->text());
    query.addBindValue(ui->roleEdit->text());
    query.exec();
    if(query.isValid()){
        QMessageBox::warning(this, "Warning","指派已存在!", QMessageBox::Yes);
        ui->roleEdit->clear();
        ui->userEdit->clear();
        ui->userEdit->setFocus();
        return;
    }
    else{
        int num = 1;
        query.exec("select * from UR");
        if(query.last()){
            num = query.value(0).toInt();
            num++;
        }
        qDebug() << num;
        query.prepare("insert into UR (ID, User, Role) values(?, ?, ?)");
        query.addBindValue(num);
        query.addBindValue(ui->userEdit->text());
        query.addBindValue(ui->roleEdit->text());
        query.exec();
        QMessageBox::warning(this, "Congratulations","用户角色指派已添加!", QMessageBox::Yes);
        accept();
    }

}

void URACreate::on_closeButton_clicked()
{
    this->close();
}
