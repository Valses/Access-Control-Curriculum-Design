#include "rolecreate.h"
#include "ui_rolecreate.h"
#include "database.h"
RoleCreate::RoleCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoleCreate)
{
    ui->setupUi(this);
    this->setWindowTitle("创建角色");
}

RoleCreate::~RoleCreate()
{
    delete ui;
}

void RoleCreate::on_yesButton_clicked()
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
    if(query.isValid()){
        QMessageBox::warning(this,"Warning","角色已存在!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }
    query.prepare("insert into Role (Role) values(?)");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    QMessageBox::warning(this,"Congratulations","角色已添加!",QMessageBox::Yes);
    accept();
}

void RoleCreate::on_closeButton_clicked()
{
    this->close();
}
