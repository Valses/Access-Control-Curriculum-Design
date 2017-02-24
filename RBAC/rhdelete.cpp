#include "rhdelete.h"
#include "ui_rhdelete.h"
#include "database.h"

RHDelete::RHDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RHDelete)
{
    ui->setupUi(this);
    this->setWindowTitle("角色层次删除");
}

RHDelete::~RHDelete()
{
    delete ui;
}

void RHDelete::on_yesButton_clicked()
{
    if(ui->role1Edit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入父角色名称!",QMessageBox::Yes);
        ui->role1Edit->setFocus();
        return;
    }
    if(ui->role2Edit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入子角色名称!",QMessageBox::Yes);
        ui->role2Edit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from Role where Role = ? ");
    query.addBindValue(ui->role1Edit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","父角色不存在!",QMessageBox::Yes);
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
        QMessageBox::warning(this,"Warning","子角色不存在!",QMessageBox::Yes);
        ui->role2Edit->clear();
        ui->role2Edit->setFocus();
        return;
    }
    query.prepare("select * from RH where Role = ? and Child = ?");
    query.addBindValue(ui->role1Edit->text());
    query.addBindValue(ui->role2Edit->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","角色层次不存在!",QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }
    query.prepare("delete from RH where Role = ? and Child = ?");
    query.addBindValue(ui->role1Edit->text());
    query.addBindValue(ui->role2Edit->text());
    query.exec();
    QMessageBox::warning(this, "Congratulations","角色层次已删除!", QMessageBox::Yes);
    accept();

}

void RHDelete::on_closeButton_clicked()
{
    this->close();
}
